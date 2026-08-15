#include "StudentImporter.hpp"

#include "CSVReader.hpp"

#include <fstream>
#include <iostream>

std::vector<StudentRow>
StudentImporter::readCSV(
    const std::string &path)
{

    std::vector<StudentRow> students;

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr
            << "Cannot open csv\n";

        return students;
    }

    std::string line;

    // 跳过标题
    std::getline(
        file,
        line);

    while (
        std::getline(
            file,
            line))
    {

        auto fields =
            CSVReader::split(line);

        if (fields.size() != 7)
        {
            std::cerr
                << "Invalid row\n";

            continue;
        }

        StudentRow row;

        row.classNumber =
            fields[0];

        row.name =
            fields[1];

        row.nameType =
            fields[2];

        row.gender =
            fields[3] == "NULL" ? "" : fields[3];

        row.genderConfidence =
            std::stoi(fields[4]);

        row.residence =
            fields[5] == "NULL" ? "" : fields[5];

        row.residenceConfidence =
            std::stoi(fields[6]);

        students.push_back(row);
    }

    return students;
}