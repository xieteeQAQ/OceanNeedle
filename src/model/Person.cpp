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

Person::Person(
    int id,
    std::string name,
    std::string nameType,
    std::string gender,
    int genderConfidence,
    std::string residence,
    int residenceConfidence)
{
    this->id = id;

    this->name = name;

    this->nameType = nameType;

    this->gender = gender;

    this->genderConfidence = genderConfidence;

    this->residence = residence;

    this->residenceConfidence = residenceConfidence;
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

void Person::setName(const std::string &name)
{
    this->name = name;
}

void Person::setNameType(const std::string &nameType)
{
    this->nameType = nameType;
}

void Person::setGender(const std::string &gender)
{
    this->gender = gender;
}

void Person::setGenderConfidence(int confidence)
{
    this->genderConfidence = confidence;
}

void Person::setResidence(const std::string &residence)
{
    this->residence = residence;
}

void Person::setResidenceConfidence(int confidence)
{
    this->residenceConfidence = confidence;
}
