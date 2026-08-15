#pragma once

#include <memory>

#include "Database.hpp"
#include "Class.hpp"

class ClassRepository
{

private:
    Database &database;

public:
    ClassRepository(
        Database &db);

    std::unique_ptr<Class> findByNumber(
        const std::string &number,
        int majorId);

    std::unique_ptr<Class> findById(
        int id);

    std::unique_ptr<Class> findOrCreateByNumber(
        const std::string &number,
        int majorId);

    bool save(
        Class &classInfo);
};