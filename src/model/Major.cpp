#include "Major.hpp"

Major::Major()
{
    id = -1;
    collegeId = -1;
}

Major::Major(
    int id,
    std::string name,
    int collegeId)
{

    this->id = id;

    this->name = name;

    this->collegeId = collegeId;
}

Major::Major(
    std::string name,
    int collegeId)
{

    id = -1;

    this->name = name;

    this->collegeId = collegeId;
}

int Major::getId() const
{
    return id;
}

void Major::setId(int id)
{
    this->id = id;
}

std::string Major::getName() const
{
    return name;
}

int Major::getCollegeId() const
{
    return collegeId;
}