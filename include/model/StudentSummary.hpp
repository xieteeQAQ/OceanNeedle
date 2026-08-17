#pragma once

#include <string>

struct StudentSummary
{
    int personId = 0;
    std::string name;
    std::string nameTpye;
    std::string gender;
    int genderConfidence = 0;
    std::string className;
    std::string majorName;
    std::string collegeName;
    std::string residence;
    int residenceConfidence = 0;
};