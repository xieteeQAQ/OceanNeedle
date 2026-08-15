#pragma once

#include "ImportDetail.hpp"
#include "Database.hpp"

class ImportDetailRepository
{
private:
    Database &database;

public:
    ImportDetailRepository(
        Database &db);

    bool save(
        ImportDetail &importDetail);
};
