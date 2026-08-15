#include "StudentValidator.hpp"

std::optional<std::string> StudentValidator::validate(
    const StudentRow &row)
{

    if (row.name.empty())
    {

        return "Name is empty";
    }

    if (
        row.nameType != "real" &&
        row.nameType != "nickname")
    {

        return "Invalid name type";
    }

    if (row.classNumber.empty())
    {

        return "Class number empty";
    }

    if (
        row.genderConfidence < 0 ||
        row.genderConfidence > 2)
    {

        return "Invalid gender confidence";
    }

    if (
        row.residenceConfidence < 0 ||
        row.residenceConfidence > 2)
    {

        return "Invalid residence confidence";
    }

    return std::nullopt;
}