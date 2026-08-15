#include "College.hpp"

College::College()
{

    int id = -1;
}

College::College(
    int id,
    std::string name)
{

    this->id = id;

    this->name = name;
}

College::College(
    std::string name)
{

    this->name = name;
}

int College::getId() const
{

    return id;
}

std::string College::getName() const
{

    return name;
}

void College::setId(int id)
{

    this->id = id;
}