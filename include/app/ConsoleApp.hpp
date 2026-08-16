#pragma once

#include "StudentService.hpp"
#include "ImportService.hpp"

#include <string>
#include <vector>
#include <functional>
#include <map>

class StudentService;
class ImportService;

class ConsoleApp
{
public:
    ConsoleApp(
        StudentService &studentService,
        ImportService &importService);

    void run();

private:
    void handleCommand(const std::string &line);
    void printHelp() const;
    void listStudents();
    void showDetail(const std::vector<std::string> &args);
    void searchStudents(const std::vector<std::string> &args);
    void importCSV(const std::vector<std::string> &args);

    StudentService &studentService;
    ImportService &importService;
    bool running = true;

    using Command = std::function<void(const std::vector<std::string> &)>;

    std::map<std::string, Command> commands =
    {
        {"help", [&](auto &args) { printHelp(); }},
        {"list", [&](auto &args) { listStudents(); }},
        {"detail", [&](auto &args){ showDetail(args); }},
        {"search", [&](auto &args) { searchStudents(args); }},
        {"import", [&](auto &args) { importCSV(args); }},
        {"exit", [&](auto &args) { running = false; }},
    };
};