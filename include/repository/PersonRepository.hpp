#pragma once

#include "Database.hpp"
#include "Person.hpp"

class PersonRepository
{

private:
    Database &database;

public:
    PersonRepository(
        Database &db);

    bool save(
        Person &person);
};