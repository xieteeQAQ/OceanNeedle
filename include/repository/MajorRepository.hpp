#pragma once

#include "Database.hpp"
#include "Major.hpp"

class MajorRepository
{

private:
    Database &database;

public:
    MajorRepository(
        Database &db);

    std::unique_ptr<Major> findByName(
        const std::string &name);

    bool save(
        Major &Major);

    std::unique_ptr<Major> findOrCreateByName(
        const std::string &name,
        int collegeId);

    std::unique_ptr<Major> findById(
        int id);

    std::vector<Major> findAll();
};
