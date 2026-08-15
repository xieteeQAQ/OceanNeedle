#include "StudentImportService.hpp"
#include "StudentValidator.hpp"

#include <iostream>

StudentImportService::StudentImportService(
    Database &db,
    PersonRepository &personRepo,
    ClassRepository &classRepo,
    StudentRepository &studentRepo)
    : database(db),
      personRepo(personRepo),
      classRepo(classRepo),
      studentRepo(studentRepo)
{
}

std::optional<std::string> StudentImportService::importStudent(
    const StudentRow &row,
    int majorId,
    DuplicatePolicy policy)
{

    std::optional<std::string> validationError =
        StudentValidator::validate(row);

    if (validationError.has_value())
    {

        return validationError.value();
    }

    auto classInfo =
        classRepo.findByNumber(
            row.classNumber,
            majorId);

    auto persons =
        personRepo.findByName(
            row.name);

    for (auto &person : persons)
    {

        if (
            studentRepo.exists(
                person.getId(),
                classInfo->getId()))
        {

            if (policy == DuplicatePolicy::SKIP)
            {

                return std::nullopt;
            }

            return "Student " + row.name + " already exists";
        }
    }

    if (!classInfo)
    {

        std::cerr
            << "Class not found: "
            << row.classNumber
            << std::endl;

        return "Class not found";
    }

    Person person(
        row.name,
        row.nameType,
        row.gender,
        row.genderConfidence,
        row.residence,
        row.residenceConfidence);

    if (!personRepo.save(person))
    {
        return "Failed to save person";
    }

    Student student(
        person.getId(),
        classInfo->getId());

    if (!studentRepo.save(student))
    {
        return "Failed to save student";
    }

    return std::nullopt;
}

ImportResult StudentImportService::importStudents(
    const std::vector<StudentRow> &rows,
    int majorId,
    ImportMode mode,
    DuplicatePolicy policy)
{

    ImportResult result;

    database.beginTransaction();

    int rowNumber = 1;

    for (const auto &row : rows)
    {

        std::optional<std::string> error =
            importStudent(
                row,
                majorId,
                policy);

        if (error.has_value())
        {

            result.addError(
                rowNumber,
                error.value());
        }
        else
        {
            result.addSuccess();
        }

        rowNumber++;

        if (mode == ImportMode::STRICT)
        {

            if (result.failedCount > 0)
            {

                database.rollback();

                return result;
            }
        }
        else if (mode == ImportMode::LENIENT)
        {

            continue;
        }
    }

    if (!database.commit())
    {
        std::cerr << "Failed to commit import transaction." << std::endl;
    }

    return result;
}