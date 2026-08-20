#pragma once

#include "StudentService.hpp"
#include "ImportService.hpp"
#include "StudentDetail.hpp"

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
    void list(const std::vector<std::string> &args);
    void showDetail(const std::vector<std::string> &args);
    void searchStudents(const std::vector<std::string> &args);
    void importCSV(const std::vector<std::string> &args);
    void findUncertainStudents(const std::vector<std::string> &args);
    void add();
    void update(const std::vector<std::string> &args);
    void removeStudent(const std::vector<std::string> &args);

    StudentService &studentService;
    ImportService &importService;
    bool running = true;

    using Command = std::function<void(const std::vector<std::string> &)>;

    std::map<std::string, Command> commands =
        {
            {"help", [&](auto &args)
             { printHelp(); }},

            {"list", [&](auto &args)
             { list(args); }},

            {"ls", [&](auto &args)
             { list(args); }},

            {"detail", [&](auto &args)
             { showDetail(args); }},

            {"dt", [&](auto &args)
             { showDetail(args); }},

            {"search", [&](auto &args)
             { searchStudents(args); }},

            {"sea", [&](auto &args)
             { searchStudents(args); }},

            {"import", [&](auto &args)
             { importCSV(args); }},

            {"imp", [&](auto &args)
             { importCSV(args); }},

            {"uncertain", [&](auto &args)
             { findUncertainStudents(args); }},

            {"uncer", [&](auto &args)
             { findUncertainStudents(args); }},

            {"add", [&](auto &args)
             { add(); }},

            {"update", [&](auto &args)
             { update(args); }},

            {"up", [&](auto &args)
             { update(args); }},

            {"remove", [&](auto &args)
             { removeStudent(args); }},

            {"rm", [&](auto &args)
             { removeStudent(args); }},

            {"exit", [&](auto &args)
             { running = false; }},

            {"quit", [&](auto &args)
             { running = false; }},

            {"q", [&](auto &args)
             { running = false; }},
    };
};