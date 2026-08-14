#include "Database.hpp"
#include "Statement.hpp"
#include "Person.hpp"
#include "Class.hpp"
#include "Major.hpp"
#include "PersonRepository.hpp"
#include "StudentRepository.hpp"
#include "ClassRepository.hpp"
#include "MajorRepository.hpp"

#include <iostream>

int main()
{

    Database db;

    db.initialize();

    MajorRepository repo(db);

    Major m1(
        "软件工程",
        1);

    if (repo.save(m1))
    {
        auto m2 = repo.findByName("软件工程");

        if (m2)
            std::cout << m2->getId();
    }

    return 0;
}