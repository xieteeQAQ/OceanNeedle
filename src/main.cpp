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

    // StudentImporter importer;

    // auto rows =
    //     importer.readCSV(
    //         "./data/SMCS_student.csv");

    // StudentImportService service(
    //     db,
    //     collegeRepo,
    //     majorRepo,
    //     personRepo,
    //     classRepo,
    //     studentRepo);

    // ImportResult result = service.importStudents(
    //     rows,
    //     1);

    // ImportRecordRepository importRecordRepo(db);

    // ImportRecord record(

    //     "students.csv",

    //     ImportRecord::getCurrentTime(),

    //     result.successCount,

    //     result.failedCount

    // );

    // if (!importRecordRepo.save(record))
    // {
    //     std::cerr << "Failed to save import record." << std::endl;
    // }

    for (int i = 1; i <= 140; ++i)
    {

        auto student = 
            studentRepo.findByPersonId(i);

        auto person = 
            personRepo.findById(i);

        auto classInfo = 
            classRepo.findById(student->getClassId());

        auto major = 
            majorRepo.findById(classInfo->getMajorId());

        auto college =
            collegeRepo.findById(major->getCollegeId());

        std::cout << "\n姓名: "
                  << person->getName()
                  << '\n'
                  << "性别: "
                  << person->getGender()
                  << '\n'
                  << "学院: "
                  << college->getName()  
                  << '\n'
                  << "专业: "
                  << major->getName()
                  << '\n'
                  << "住址: "
                  << person->getResidence()
                  << '\n';
    }
}