#include "Database.hpp"
#include "Statement.hpp"
#include "Person.hpp"

#include <iostream>

int main()
{

    // Database db;

    // if (!db.isConnected())
    // {
    //     return 1;
    // }

    // if (db.initialize())
    // {
    //     std::cout
    //         << "Database initialized."
    //         << std::endl;
    // }
    // else
    // {
    //     std::cout
    //         << "Database initialized failed."
    //         << std::endl;
    // }

    Person p(
        "陈柏明",
        "real",
        "男",
        2,
        "广东东莞",
        2
    );


    std::cout
        << p.getName()
        << std::endl;

    return 0;
}