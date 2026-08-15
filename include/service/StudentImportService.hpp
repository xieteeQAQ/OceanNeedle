#pragma once

#include "Database.hpp"
#include "StudentRow.hpp"

#include "PersonRepository.hpp"
#include "ClassRepository.hpp"
#include "StudentRepository.hpp"
#include "MajorRepository.hpp"
#include "CollegeRepository.hpp"

#include "ImportResult.hpp"
#include "ImportMode.hpp"

#include <optional>

class StudentImportService
{

private:
    Database &database;

    CollegeRepository &collegeRepo;

    MajorRepository &majorRepo;

    PersonRepository &personRepo;

    ClassRepository &classRepo;

    StudentRepository &studentRepo;

public:
    StudentImportService(
        Database &db,
        CollegeRepository &collegeRepo,
        MajorRepository &majorRepo,
        PersonRepository &personRepo,
        ClassRepository &classRepo,
        StudentRepository &studentRepo);

        ImportDetailData importStudent(
        const StudentRow &row,
        DuplicatePolicy policy = DuplicatePolicy::SKIP);

    ImportResult importStudents(
        const std::vector<StudentRow> &rows,
        int majorId,
        ImportMode mode = ImportMode::STRICT,
        DuplicatePolicy policy = DuplicatePolicy::SKIP);

    std::optional<Student> findByPersonAndClass(
        int personId,
        int classId);
};