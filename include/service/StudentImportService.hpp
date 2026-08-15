#pragma once

#include "Database.hpp"
#include "StudentRow.hpp"

#include "PersonRepository.hpp"
#include "ClassRepository.hpp"
#include "StudentRepository.hpp"

#include "ImportResult.hpp"
#include "ImportMode.hpp"

#include <optional>

class StudentImportService
{

private:
    Database &database;

    PersonRepository &personRepo;

    ClassRepository &classRepo;

    StudentRepository &studentRepo;

public:
    StudentImportService(
        Database &db,
        PersonRepository &personRepo,
        ClassRepository &classRepo,
        StudentRepository &studentRepo);

    std::optional<std::string> importStudent(
        const StudentRow &row,
        int majorId,
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