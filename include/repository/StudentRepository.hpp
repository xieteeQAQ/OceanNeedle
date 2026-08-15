#pragma once

#include "Database.hpp"
#include "Student.hpp"

class StudentRepository
{

private:
    Database &database;

public:
    StudentRepository(
        Database &db);

    bool save(
        Student &student);

    std::unique_ptr<Student> findByPersonId(
        int personId);

    bool exists(
        int personId,
        int classId);
};