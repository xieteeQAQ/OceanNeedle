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

#include <iostream>

int main()
{

    Database db;

    db.initialize();

    PersonRepository repo(db);

    auto person =
        repo.findById(
            1);

    StudentRepository studentRepo(db);

    auto student =
        studentRepo.findByPersonId(
            person->getId());

    ClassRepository classRepo(db);

    auto Class =
        classRepo.findById(
            student->getClassId());

    MajorRepository majorRepo(db);

    auto major =
        majorRepo.findById(
            Class->getMajorId());

    CollegeRepository collegeRepo(db);

    auto college =
        collegeRepo.findById(
            major->getCollegeId());

    if (college)
    {

        std::cout
            << "Person found: "
            << person->getName()
            << std::endl;

        std::cout
            << "Class found: "
            << Class->getClassNumber()
            << std::endl;

        std::cout
            << "Major found: "
            << major->getName()
            << std::endl;

        std::cout
            << "College found: "
            << college->getName()
            << std::endl;
    }
    else
    {
        std::cout
            << "College not found"
            << std::endl;
    }

    return 0;
}