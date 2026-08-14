#include "Class.hpp"

Class::Class()
{

    id = -1;

    majorId = -1;
}

Class::Class(
    int id,
    std::string classNumber,
    int majorId)
{

    this->id = id;

    this->classNumber = classNumber;

    this->majorId = majorId;
}

Class::Class(
    std::string classNumber,
    int majorId
)
{

    this->id = -1;

    this->classNumber = classNumber;

    this->majorId = majorId;

}

int Class::getId() const
{
    return id;
}

std::string Class::getClassNumber() const
{
    return classNumber;
}

int Class::getMajorId() const
{
    return majorId;
}

void Class::setId(int id)
{
    this->id = id;
}