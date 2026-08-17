#pragma once

#include <string>

struct StudentDraft
{
    std::string name;
    std::string nameType;
    std::string gender;
    int genderConfidence = 0;

    std::string residence;
    int residenceConfidence = 0;

    std::string collegeName;
    std::string majorName;
    std::string className;
};