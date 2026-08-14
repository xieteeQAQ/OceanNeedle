#include "Student.hpp"

Student::Student(
    int personId,
    int classId)
{
    this->personId = personId;

    this->classId = classId;
}

int Student::getPersonId() const
{
    return personId;
}

int Student::getClassId() const
{
    return classId;
}