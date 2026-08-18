#pragma once

#include "StudentRepository.hpp"
#include "PersonRepository.hpp"
#include "ClassRepository.hpp"
#include "MajorRepository.hpp"
#include "CollegeRepository.hpp"

#include "StudentSummary.hpp"
#include "StudentDetail.hpp"
#include "StudentDraft.hpp"

#include <optional>
#include <vector>

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

    std::vector<StudentSummary> listAllStudents();

    std::optional<StudentDetail> getStudentDetail(int personId);

    std::vector<StudentSummary> searchStudents(const std::string &keyword);

    std::vector<StudentSummary> findUncertainStudents(const std::string &field, int confidence);

    bool addStudent(const StudentDraft &draft);

    bool updateStudent(int personId, const StudentDraft &draft);

    bool deleteStudent(int personId);
};