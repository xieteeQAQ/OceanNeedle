#pragma once

#include "Database.hpp"
#include "Student.hpp"

#include <vector>

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

    std::vector<Student> findAll();

    bool updateClass(int personId, int newClassId);
};