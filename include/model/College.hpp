#pragma once

#include <string>

class College
{

private:
    int id;

    std::string name;

public:
    College();

    College(
        int id,
        std::string name);

    College(
        std::string name);

    int getId() const;

    void setId(int id);

    std::string getName() const;
};