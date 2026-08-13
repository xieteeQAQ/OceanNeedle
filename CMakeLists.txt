cmake_minimum_required(VERSION 3.20)

project(OceanNeedle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 查找 SQLite
find_package(SQLite3 REQUIRED)


include_directories(include)


add_executable(OceanNeedle
    src/main.cpp
    src/Database.cpp
    src/Statement.cpp
    src/Person.cpp
)


target_link_libraries(OceanNeedle 
    SQLite3::SQLite3
)