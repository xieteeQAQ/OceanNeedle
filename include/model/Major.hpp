#pragma once

#include <string>

class Major
{

private:
    int id;

    std::string name;

    int collegeId;

public:
    Major();

    Major(
        int id,
        std::string name,
        int collegeId);

    Major(
        std::string name,
        int collegeId);

    int getId() const;

    void setId(int id);

    std::string getName() const;

    int getCollegeId() const;
};