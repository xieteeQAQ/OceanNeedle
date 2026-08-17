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

    Person(
        int id,
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
    void setId(int id);
    void setName(const std::string &name);
    void setNameType(const std::string &nameType);
    void setGender(const std::string &gender);
    void setGenderConfidence(int confidence);
    void setResidence(const std::string &residence);
    void setResidenceConfidence(int confidence);
};