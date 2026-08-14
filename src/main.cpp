#include "Database.hpp"
#include "Statement.hpp"
#include "Person.hpp"
#include "Class.hpp"
#include "PersonRepository.hpp"
#include "StudentRepository.hpp"
#include "ClassRepository.hpp"

#include <iostream>

int main()
{

    Database db;

    db.initialize();

    ClassRepository repo(db);

    auto c = repo.findByNumber(
        "1264",
        1);

    if (c)
    {
        std::cout << c->getId()
                  << c->getClassNumber()
                  << c->getMajorId()
                  << "\n";
    }

    return 0;
}