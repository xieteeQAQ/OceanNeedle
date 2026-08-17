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
            << "cannot open csv \'" << path << "\'\n";

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

        if (fields.size() != 10)
        {
            std::cerr
                << "Invalid row\n";

            continue;
        }

        StudentRow row;

        row.college =
            fields[0];

        row.major =
            fields[1];

        row.classNumber =
            fields[2];

        row.role =
            fields[3];

        row.name =
            fields[4];

        row.nameType =
            fields[5];

        row.gender =
            fields[6] == "NULL" ? "" : fields[6];

        row.genderConfidence =
            std::stoi(fields[7]);

        row.residence =
            fields[8] == "NULL" ? "" : fields[8];

        row.residenceConfidence =
            std::stoi(fields[9]);

        students.push_back(row);
    }

    return students;
}