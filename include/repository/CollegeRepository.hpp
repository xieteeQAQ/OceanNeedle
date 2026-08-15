#pragma once

#include "Database.hpp"
#include "College.hpp"

class CollegeRepository
{
private:
    Database &database;

public:
    CollegeRepository(
        Database &db);

    bool save(
        College &college);

    std::unique_ptr<College> findByName(
        const std::string &name);

    std::unique_ptr<College> findById(
        int id);

    std::unique_ptr<College> findOrCreateByName(
        const std::string &name);
};