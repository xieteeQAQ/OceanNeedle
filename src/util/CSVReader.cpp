#include "CSVReader.hpp"

std::vector<std::string>
CSVReader::split(
    const std::string &line)
{

    std::vector<std::string> result;

    std::string field;

    for (char c : line)
    {

        if (c == ',')
        {

            result.push_back(field);

            field.clear();
        }
        else
        {
            field += c;
        }
    }

    result.push_back(field);

    return result;
}