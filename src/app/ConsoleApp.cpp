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

void ConsoleApp::list(const std::vector<std::string> &args)
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

    bool listCollege = false;
    bool listMajor = false;
    bool listClass = false;
    bool listStudents = false;

    if (args.empty())
    {
        listStudents = true;
    }
    else if (args[0][0] == '-')
    {
        std::string arg = args[0];

        for (char a : arg)
        {
            if (a == 'C')
                listCollege = true;
            else if (a == 'm')
                listMajor = true;
            else if (a == 'c')
                listClass = true;
            else if (a == 's')
                listStudents = true;
            else if (a == 'a')
            {
                listCollege = true;
                listMajor = true;
                listClass = true;
                listStudents = true;
            }
        }
    }
    else
    {

    }

    if (listCollege)
    {
        auto colleges = studentService.listAllColleges();

        for (const auto &c : colleges)
        {
            std::cout
                << "college ID: " << c.getId()
                << ", name: " << c.getName()
                << "\n";
        }
    }

    if (listMajor)
    {
        auto majors = studentService.listAllMajors();

        for (const auto &m : majors)
        {
            std::cout
                << "major ID: " << m.getId()
                << ", name: " << m.getName()
                << ", college ID: " << m.getCollegeId()
                << "\n";
        }
    }

    if (listClass)
    {
        auto classes = studentService.listAllClass();

        for (const auto &c : classes)
        {
            std::cout
                << "class ID: " << c.getId()
                << ", number: " << c.getClassNumber()
                << ", major ID: " << c.getMajorId()
                << "\n";
        }
    }

    if (listStudents)
    {
        auto students = studentService.listAllStudents();
        for (const auto &s : students)
        {
            std::cout
                << "student ID: " << s.personId
                << ", name: " << s.name
                << ", gender: " << s.gender
                << (s.genderConfidence == 0 ? "[?]" : "")
                << ", class: " << s.className
                << ", major: " << s.majorName
                << ", college: " << s.collegeName
                << "\n";
        }
    }
}

void ConsoleApp::printHelp() const
{
    std::cout << R"(
AVAILABLE COMMANDS:
        help                                            print help

        list/ls                                         list all students

        add                                             add student

        update/up <id>                                  update student data

        detail/dt <id>                                  view student details

        search/sea <keyword>                            search students

        uncertain/uncer [gender|residence] [0|1]        find students with low-confidence data

        remove/rm <id>                                  delete a student

        import/imp <csv_path>                           import CSV

        exit/quit/q                                     exit process
        )"
              << '\n';
}

void ConsoleApp::showDetail(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "usage: detail/dt <id>\n";
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
        std::cout << "usage: search/sea <keyword>\n";
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
        std::cout << "usage: import/imp <csv_path>\n";
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

void ConsoleApp::findUncertainStudents(const std::vector<std::string> &args)
{
    std::string field = "all";
    int confidence = -1;

    if (!args.empty())
    {
        if (args[0] == "gender" ||
            args[0] == "residence" ||
            args[0] == "all")
        {
            field = args[0];
        }
        else
        {
            std::cout
                << "unknown field: " << args[0]
                << " (use gender/residence/all)\n";
            return;
        }
    }

    if (args.size() >= 2)
    {
        std::istringstream iss(args[1]);
        int value = 0;

        if (!(iss >> value) || (value != 0 && value != 1))
        {
            std::cout << "confidence must be 0 or 1\n";
            return;
        }

        confidence = value;
    }

    auto students = studentService.findUncertainStudents(field, confidence);

    if (students.empty())
    {
        std::cout << "no uncertain students found\n";
        return;
    }

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

void ConsoleApp::add()
{
    /*
    struct StudentDraft
    {
        std::string name;
        std::string nameType;
        std::string gender;
        int genderConfidence = 0;

        std::string residence;
        int residenceConfidence = 0;

        std::string collegeName;
        std::string majorName;
        std::string className;
    };
    */

    std::string line;

    StudentDraft draft;

    std::cout << "\rname: " << std::flush;
    std::getline(std::cin, draft.name);

    std::cout << "\rnameType: " << std::flush;
    std::getline(std::cin, draft.nameType);

    std::cout << "\rgender: " << std::flush;
    std::getline(std::cin, draft.gender);

    std::cout << "\rgenderConfidence (0/1/2): " << std::flush;
    std::getline(std::cin, line);
    draft.genderConfidence = std::stoi(line);

    std::cout << "\rresidence: " << std::flush;
    std::getline(std::cin, draft.residence);

    std::cout << "\rresidenceConfidence: " << std::flush;
    std::getline(std::cin, line);
    draft.residenceConfidence = std::stoi(line);

    std::cout << "\rcollege: " << std::flush;
    std::getline(std::cin, draft.collegeName);

    std::cout << "\rmajor: " << std::flush;
    std::getline(std::cin, draft.majorName);

    std::cout << "\rclass: " << std::flush;
    std::getline(std::cin, draft.className);

    std::cout << "Confirm adding? (y/n): " << std::flush;
    std::string confirm;
    std::getline(std::cin, confirm);

    if (confirm != "y" && confirm != "Y")
    {
        std::cout << "add cancel\n";
        return;
    }

    if (studentService.addStudent(draft))
    {
        std::cout << "add student success\n";
    }
    else
    {
        std::cout << "add student failed\n";
    }
}

void ConsoleApp::update(const std::vector<std::string> &args)
{
    /*
    struct StudentDraft
    {
        std::string name;
        std::string nameType;
        std::string gender;
        int genderConfidence = 0;

        std::string residence;
        int residenceConfidence = 0;

        std::string collegeName;
        std::string majorName;
        std::string className;
    };
    */

    if (args.empty())
    {
        std::cout << "usage: update/up <id>\n";
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

    StudentDraft draft;

    draft.name = detail->name;
    draft.nameType = detail->nameType;
    draft.gender = detail->gender;
    draft.genderConfidence = detail->genderConfidence;
    draft.residence = detail->residence;
    draft.residenceConfidence = detail->residenceConfidence;
    draft.collegeName = detail->collegeName;
    draft.majorName = detail->majorName;
    draft.className = detail->className;

    std::string input;

    std::cout << "name [" << draft.name << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.name = input;

    std::cout << "nameType [" << draft.nameType << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.nameType = input;

    std::cout << "gender [" << draft.gender << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.gender = input;

    std::cout << "genderConfidence [" << draft.genderConfidence << "] (0/1/2): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.genderConfidence = std::stoi(input);

    std::cout << "residence [" << draft.residence << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.residence = input;

    std::cout << "residenceConfidence [" << draft.residenceConfidence << "] (0/1/2): " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.residenceConfidence = std::stoi(input);

    std::cout << "college [" << draft.collegeName << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.collegeName = input;

    std::cout << "major [" << draft.majorName << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.majorName = input;

    std::cout << "class [" << draft.className << "]: " << std::flush;
    std::getline(std::cin, input);
    if (!input.empty())
        draft.className = input;

    std::cout << "Confirm update? (y/n): " << std::flush;
    std::getline(std::cin, input);

    if (input != "y" && input != "Y")
    {
        std::cout << "update cancel\n";
        return;
    }

    if (studentService.updateStudent(id, draft))
    {
        std::cout << "update student success\n";
    }
    else
    {
        std::cout << "update student failed\n";
    }
}

void ConsoleApp::removeStudent(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "usage: remove/rm <id>\n";
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
        << "You are about to delete:\n"
        << "ID: " << detail->personId << "\n"
        << "name: " << detail->name << "\n"
        << "class: " << detail->className << "\n"
        << "major: " << detail->majorName << "\n"
        << "college: " << detail->collegeName << "\n";

    std::cout << "Confirm delete? (y/n): " << std::flush;
    std::string confirm;
    std::getline(std::cin, confirm);

    if (confirm != "y" && confirm != "Y")
    {
        std::cout << "delete cancel\n";
        return;
    }

    if (studentService.deleteStudent(id))
    {
        std::cout << "delete student success\n";
    }
    else
    {
        std::cout << "delete student failed\n";
    }
}