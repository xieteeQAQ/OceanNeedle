#pragma once

#include <string>

struct StudentDetail
{
    int personId = 0;
    std::string name;
    std::string nameType;
    std::string gender;
    int genderConfidence;
    std::string residence;
    int residenceConfidence;
    std::string className;
    std::string majorName;
    std::string collegeName;
};