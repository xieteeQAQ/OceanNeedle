#pragma once

#include "ImportRecord.hpp"
#include "Database.hpp"

class ImportRecordRepository
{

private:
    Database &database;

public:
    ImportRecordRepository(
        Database &database);

    bool save(
        ImportRecord &record);
};
