#pragma once

#include "StudentRow.hpp"

#include <string>
#include <optional>

class StudentValidator
{

public:
    static std::optional<std::string> validate(
        const StudentRow &row);
};