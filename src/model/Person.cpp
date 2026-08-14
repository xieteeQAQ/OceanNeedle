#include "Person.hpp"

Person::Person()
{

    id = -1;

    genderConfidence = 0;

    residenceConfidence = 0;
}

Person::Person(
    std::string name,
    std::string nameType,
    std::string gender,
    int genderConfidence,
    std::string residence,
    int residenceConfidence)
{

    this->name = name;

    this->nameType = nameType;

    this->gender = gender;

    this->genderConfidence =
        genderConfidence;

    this->residence =
        residence;

    this->residenceConfidence =
        residenceConfidence;

    id = -1;
}

int Person::getId() const
{
    return id;
}

void Person::setId(int id)
{
    this->id = id;
}

std::string Person::getName() const
{
    return name;
}

std::string Person::getNameType() const
{
    return nameType;
}

std::string Person::getGender() const
{
    return gender;
}

int Person::getGenderConfidence() const
{
    return genderConfidence;
}

std::string Person::getResidence() const
{
    return residence;
}

int Person::getResidenceConfidence() const
{
    return residenceConfidence;
}