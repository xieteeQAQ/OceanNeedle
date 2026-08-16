#include "StudentImportService.hpp"
#include "StudentValidator.hpp"

#include <iostream>

StudentImportService::StudentImportService(
    Database &db,
    CollegeRepository &collegeRepo,
    MajorRepository &majorRepo,
    PersonRepository &personRepo,
    ClassRepository &classRepo,
    StudentRepository &studentRepo)
    : database(db),
      collegeRepo(collegeRepo),
      majorRepo(majorRepo),
      personRepo(personRepo),
      classRepo(classRepo),
      studentRepo(studentRepo)
{
}

ImportDetailData StudentImportService::importStudent(
    const StudentRow &row,
    DuplicatePolicy policy)
{

    ImportDetailData importDetailData;

    std::optional<std::string> validationError =
        StudentValidator::validate(row);

    if (validationError.has_value())
    {

        importDetailData = {
            -1,
            row.name,
            ImportStatus::FAILED,
            validationError.value()};

        return importDetailData;
    }

    auto majorInfo =
        majorRepo.findByName(
            row.major);

    if (!majorInfo)
    {

        importDetailData = {
            -1,
            row.name,
            ImportStatus::FAILED,
            "Major not found"};

        return importDetailData;
    }

    auto classInfo =
        classRepo.findByNumber(
            row.classNumber,
            majorInfo->getId());

    if (!classInfo)
    {

        importDetailData = {
            -1,
            row.name,
            ImportStatus::FAILED,
            "Class not found"};

        return importDetailData;
    }

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

                importDetailData = {
                    -1,
                    row.name,
                    ImportStatus::SKIPPED,
                    "Student already exists"};

                return importDetailData;
            }

            importDetailData = {
                -1,
                row.name,
                ImportStatus::FAILED,
                "Student already exists"};

            return importDetailData;
        }
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

        importDetailData = {
            -1,
            row.name,
            ImportStatus::FAILED,
            "Failed to save person"};

        return importDetailData;
    }

    Student student(
        person.getId(),
        classInfo->getId());

    if (!studentRepo.save(student))
    {

        importDetailData = {
            -1,
            row.name,
            ImportStatus::FAILED,
            "Failed to save person"};

        return importDetailData;
    }

    importDetailData = {
        -1,
        row.name,
        ImportStatus::SUCCESS,
        ""};

    return importDetailData;
}

ImportResult StudentImportService::importStudents(
    const std::vector<StudentRow> &rows,
    ImportMode mode,
    DuplicatePolicy policy)
{

    ImportResult result;

    database.beginTransaction();

    int rowNumber = 1;

    for (const auto &row : rows)
    {

        auto imporDetailData =
            importStudent(
                row,
                policy);

        imporDetailData.rowNumber = rowNumber;

        result.details.push_back(imporDetailData);

        if (imporDetailData.status == ImportStatus::FAILED)
        {

            result.addFailed();
        }
        else if (imporDetailData.status == ImportStatus::SKIPPED)
        {

            result.addSkipped();
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