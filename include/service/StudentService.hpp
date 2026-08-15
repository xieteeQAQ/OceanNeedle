#pragma once

#include "StudentRepository.hpp"
#include "PersonRepository.hpp"
#include "ClassRepository.hpp"
#include "MajorRepository.hpp"
#include "CollegeRepository.hpp"

class StudentService
{

private:
    StudentRepository &studentRepo;

    PersonRepository &personRepo;

    ClassRepository &classRepo;

    MajorRepository &majorRepo;

    CollegeRepository &collegeRepo;

public:
    StudentService(
        StudentRepository &studentRepo,
        PersonRepository &personRepo,
        ClassRepository &classRepo,
        MajorRepository &majorRepo,
        CollegeRepository &collegeRepo);

    void showStudentDetail(
        int studentId);
};