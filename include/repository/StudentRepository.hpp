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
};