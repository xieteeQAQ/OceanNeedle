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
#include "ImportService.hpp"

#include "StudentImporter.hpp"
#include "StudentImportService.hpp"
#include "StudentValidator.hpp"
#include "CSVReader.hpp"

#include "ConsoleApp.hpp"

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

    StudentImportService studentImportService(
        db,
        collegeRepo,
        majorRepo,
        personRepo,
        classRepo,
        studentRepo);

    ImportRecordRepository recordRepo(
        db);

    ImportDetailRepository detailRepo(
        db);

    StudentService studentService(
        db,
        studentRepo,
        personRepo,
        classRepo,
        majorRepo,
        collegeRepo);

    ImportService importService(
        importer,
        studentImportService,
        recordRepo,
        detailRepo);

    ConsoleApp consoleApp(
        studentService,
        importService);

    consoleApp.run();

}