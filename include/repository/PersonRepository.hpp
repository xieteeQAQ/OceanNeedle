#pragma once

#include "Database.hpp"
#include "Person.hpp"

#include <vector>

class PersonRepository
{

private:
    Database &database;

public:
    PersonRepository(
        Database &db);

    bool save(
        Person &person);

    std::vector<Person> findByName(
        const std::string &name);

    std::unique_ptr<Person> findById(
        int id);

    std::vector<Person> findOrCreateByName(
        const std::string &name,
        const std::string &nameType,
        const std::string &gender,
        int genderConfidence,
        const std::string &residence,
        int residenceConfidence);
};