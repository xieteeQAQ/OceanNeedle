#pragma once

#include <string>

class Class
{

private:
    int id;

    std::string classNumber;

    int majorId;

public:
    Class();

    Class(
        int id,
        std::string classNumber,
        int majorId);

    Class(
        std::string classNumber,
        int majorId);

    int getId() const;

    std::string getClassNumber() const;

    int getMajorId() const;

    void setId(int id);
};