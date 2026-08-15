#include "Database.hpp"
#include "Statement.hpp"

#include "Person.hpp"
#include "Class.hpp"
#include "Major.hpp"
#include "College.hpp"
#include "Student.hpp"
#include "ImportRecord.hpp"

#include "PersonRepository.hpp"
#include "StudentRepository.hpp"
#include "ClassRepository.hpp"
#include "MajorRepository.hpp"
#include "CollegeRepository.hpp"
#include "ImportRecordRepository.hpp"

#include "StudentService.hpp"
#include "StudentImporter.hpp"
#include "StudentImportService.hpp"
#include "StudentValidator.hpp"
#include "CSVReader.hpp"

#include <iostream>

int main()
{

    Database db;

    db.initialize();

    PersonRepository personRepo(db);

    ClassRepository classRepo(db);

    MajorRepository majorRepo(db);

    CollegeRepository collegeRepo(db);

    StudentRepository studentRepo(db);

    StudentImporter importer;

    for (int i = 1; i <= 4; ++i)
    {

        std::string class_number = "126" + std::to_string(i);

        Class c(
            class_number,
            2);
        
        if (classRepo.save(c))
        {

            std::cout << class_number + "insert success\n";
        }
    }

    auto rows =
        importer.readCSV(
            "./data/students.csv");

    for (const auto &row : rows)
    {

        std::cout
            << row.classNumber
            << ", "
            << row.name
            << ", "
            << row.nameType
            << ", "
            << row.gender
            << ", "
            << row.genderConfidence
            << ", "
            << row.residence
            << ", "
            << row.residenceConfidence
            << std::endl;
    }

    StudentImportService service(
        db,
        personRepo,
        classRepo,
        studentRepo);

    ImportResult result = service.importStudents(
        rows,
        1);

    std::cout
        << "Success: "
        << result.successCount
        << ", Failed: "
        << result.failedCount
        << std::endl;

    if (result.failedCount > 0)
    {

        for (const auto &error : result.errors)
        {

            std::cout
                << "Row "
                << error.row
                << ": "
                << error.reason
                << std::endl;
        }
    }

    ImportRecordRepository importRecordRepo(db);

    ImportRecord record(

        "students.csv",

        ImportRecord::getCurrentTime(),

        result.successCount,

        result.failedCount

    );

    std::cout << record.getFileName()
              << ", "
              << record.getImportTime()
              << ", "
              << record.getSuccessCount()
              << ", "
              << record.getFailedCount()
              << std::endl;

    if (!importRecordRepo.save(record))
    {
        std::cerr << "Failed to save import record." << std::endl;
    }
}