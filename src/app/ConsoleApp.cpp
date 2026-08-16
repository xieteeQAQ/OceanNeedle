#include "ConsoleApp.hpp"

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

        std::cout << "> " << std::flush;
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
        std::string className;
        std::string majorName;
        std::string collegeName;
        std::string residence;
    }
    */

    auto students = studentService.listAllStudents();

    for (const auto &s : students)
    {

        std::cout
            << "id: " << s.personId << '\n'
            << "name: " << s.name << '\n'
            << "gender: " << s.gender << '\n'
            << "class: " << s.className << '\n'
            << "major: " << s.majorName << '\n'
            << "college: " << s.collegeName << '\n'
            << "residence: " << s.residence << '\n';
    }
}

void ConsoleApp::printHelp() const
{
    std::cout
        << "AVAILABLE COMMANDS:\n"
        << "  help                  print help\n\n"
        << "  list                  list all students\n\n"
        << "  detail <id>           view student details\n\n"
        << "  search <keyword>      search students\n\n"
        << "  import <csv_path>     import CSV\n\n"
        << "  exit                  exit process\n\n";
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
        << "name: " << detail->name << "\n"
        << "nameType: " << detail->nameType << "\n"
        << "gender: " << detail->gender << "\n"
        << "residence: " << detail->residence << "\n"
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
            << "id: " << s.personId
            << ", name: " << s.name
            << ", class: " << s.className
            << ", college: " << s.majorName
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

    // TODO: 等 ImportService 实现后再接入
    std::cout << "the import functionality is not yet implemented\n";
}