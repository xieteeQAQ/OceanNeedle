#include "StudentService.hpp"

#include <iostream>

StudentService::StudentService(
    StudentRepository &studentRepo,
    PersonRepository &personRepo,
    ClassRepository &classRepo,
    MajorRepository &majorRepo,
    CollegeRepository &collegeRepo)
    : studentRepo(studentRepo),
      personRepo(personRepo),
      classRepo(classRepo),
      majorRepo(majorRepo),
      collegeRepo(collegeRepo)
{
}

void StudentService::showStudentDetail(
    int studentId)
{
    auto student =
        studentRepo.findByPersonId(
            studentId);

    if (!student)
    {
        std::cout
            << "Student not found\n";

        return;
    }

    auto person =
        personRepo.findById(
            student->getPersonId());

    auto Class =
        classRepo.findById(
            student->getClassId());

    auto major =
        majorRepo.findById(
            Class->getMajorId());

    auto college =
        collegeRepo.findById(
            major->getCollegeId());

    std::cout
        << "姓名: "
        << person->getName()
        << '\n';

    std::cout
        << "班级: "
        << Class->getClassNumber()
        << '\n';

    std::cout
        << "专业: "
        << major->getName()
        << '\n';

    std::cout
        << "学院: "
        << college->getName()
        << '\n';
}