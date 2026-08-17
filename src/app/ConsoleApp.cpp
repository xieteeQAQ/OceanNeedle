#include "ConsoleApp.hpp"
#include "Confidence.hpp"

#include <iostream>
#include <sstream>

ConsoleApp::ConsoleApp(
    StudentService &studentService,
    ImportService &importService)
    : studentService(studentService), importService(importService)
{
}

void ConsoleApp::run()
{
    std::string line;

    while (running)
    {

        std::cout << "OceanNeedle> " << std::flush;
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        handleCommand(line);
    }
}

void ConsoleApp::handleCommand(const std::string &line)
{

    std::istringstream iss(line);

    std::string command;
    iss >> command;

    if (command.empty())
        return;

    std::vector<std::string> args;
    std::string arg;

    while (iss >> arg)
    {

        args.push_back(arg);
    }

    auto it = commands.find(command);

    if (it != commands.end())
    {

        it->second(args);
    }
    else
    {

        std::cout << "command not found: " << command << "\n";
        printHelp();
    }
}

void ConsoleApp::listStudents()
{

    /*
    StudentSummary
    {
        int personId = 0;
        std::string name;
        std::string gender;
        int genderConfidence = 0;
        std::string className;
        std::string majorName;
        std::string collegeName;
        std::string residence;
        int residenceConfidence = 0;
    }
    */

    auto students = studentService.listAllStudents();

    for (const auto &s : students)
    {
        std::cout
            << "id: " << s.personId
            << ", name: " << s.name
            << ", gender: " << s.gender
            << (s.genderConfidence == 0 ? "[?]" : "")
            << ", class: " << s.className
            << ", major: " << s.majorName
            << ", college: " << s.collegeName
            << "\n";
    }
}

void ConsoleApp::printHelp() const
{
    std::cout << R"(
AVAILABLE COMMANDS:
        help                  print help

        list                  list all students

        detail <id>           view student details

        search <keyword>      search students

        import <csv_path>     import CSV

        exit/quit/q           exit process)"
              << '\n';
}

void ConsoleApp::showDetail(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "usage: detail <id>\n";
        return;
    }

    int id = 0;
    std::istringstream iss(args[0]);

    if (!(iss >> id))
    {
        std::cout << "id must be number\n";
        return;
    }

    auto detail = studentService.getStudentDetail(id);

    if (!detail)
    {
        std::cout << "student not found: " << id << "\n";
        return;
    }

    std::cout
        << "ID: " << detail->personId << "\n"
        << "name: " << detail->name
        << " (nameType: " << detail->nameType << ")" << "\n"
        << "gender: " << detail->gender
        << " (confidence: " << confidenceLabel(detail->genderConfidence) << ")" << "\n"
        << "residence: " << detail->residence
        << " (confidence: " << confidenceLabel(detail->residenceConfidence) << ")" << "\n"
        << "class: " << detail->className << "\n"
        << "major: " << detail->majorName << "\n"
        << "college: " << detail->collegeName << "\n";
}

void ConsoleApp::searchStudents(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "usage: search <keyword>\n";
        return;
    }

    std::string keyword;

    for (size_t i = 0; i < args.size(); ++i)
    {
        if (i > 0)
            keyword += ' ';

        keyword += args[i];
    }

    auto results = studentService.searchStudents(keyword);

    if (results.empty())
    {
        std::cout << "no matching students found\n";
        return;
    }

    for (const auto &s : results)
    {
        std::cout
            << "ID: " << s.personId
            << ", name: " << s.name
            << ", class: " << s.className
            << ", major: " << s.majorName
            << ", college: " << s.collegeName
            << "\n";
    }
}

void ConsoleApp::importCSV(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "usage: import <csv_path>\n";
        return;
    }

    const std::string &filename = args[0];

    auto result = importService.importFromCSV(filename);

    if (result.has_value())
    {
        std::cout << "import csv success\n"
                  << "success: " << result->successCount << ", "
                  << "skipped: " << result->skippedCount << ", "
                  << "failed: " << result->failedCount << '\n';
    }
    else
    {
        std::cout << "import failed or no data\n";
    }
}

void ConsoleApp::findUncertainStudents()
{
    auto students = studentService.findUncertainStudents();

    for (const auto &s : students)
    {
        std::cout
            << "ID: " << s.personId
            << ", name: " << s.name
            << ", gender: " << s.gender
            << (s.genderConfidence == 0 ? "[?]" : "")
            << ", class: " << s.className
            << ", major: " << s.majorName
            << ", college: " << s.collegeName
            << "\n";
    }
}