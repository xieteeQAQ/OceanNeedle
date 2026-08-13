#pragma once

#include <string>

class Person
{

private:
    int id;

    std::string name;

    std::string nameType;

    std::string gender;

    int genderConfidence;

    std::string residence;

    int residenceConfidence;

public:
    Person();

    Person(
        std::string name,
        std::string nameType,
        std::string gender,
        int genderConfidence,
        std::string residence,
        int residenceConfidence);

    int getId() const;

    std::string getName() const;

    std::string getNameType() const;

    std::string getGender() const;

    int getGenderConfidence() const;

    std::string getResidence() const;

    int getResidenceConfidence() const;
};