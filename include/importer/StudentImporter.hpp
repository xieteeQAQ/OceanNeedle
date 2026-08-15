#pragma once

#include "StudentService.hpp"
#include "StudentRow.hpp"

#include <string>

class StudentImporter
{

public:
    std::vector<StudentRow>
    readCSV(
        const std::string &path);
};
