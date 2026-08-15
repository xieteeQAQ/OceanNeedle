#pragma once

#include <string>
#include <vector>

class CSVReader
{

public:
    static std::vector<std::string> split(
        const std::string &line);
};