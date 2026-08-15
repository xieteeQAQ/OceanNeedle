#include "Database.hpp"
#include "Statement.hpp"
#include "Person.hpp"
#include "Class.hpp"
#include "Major.hpp"
#include "College.hpp"
#include "PersonRepository.hpp"
#include "StudentRepository.hpp"
#include "ClassRepository.hpp"
#include "MajorRepository.hpp"
#include "CollegeRepository.hpp"
#include "StudentService.hpp"

#include <iostream>

int main()
{

    Database db;

    db.initialize();

    PersonRepository personRepo(
        db);

    StudentRepository studentRepo(
        db);

    ClassRepository classRepo(
        db);

    MajorRepository majorRepo(
        db);

    CollegeRepository collegeRepo(
        db);

    StudentService studentService(
        studentRepo,
        personRepo,
        classRepo,
        majorRepo,
        collegeRepo);
    
    studentService.showStudentDetail(
        1);
}