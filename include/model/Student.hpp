#pragma once

#include "Person.hpp"

class Student
{
private:
    int personId;

    int classId;

public:
    Student(
        int personId,
        int classId);

    int getPersonId() const;

    int getClassId() const;
};