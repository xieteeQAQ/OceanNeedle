cmake_minimum_required(VERSION 3.20)

project(OceanNeedle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 SQLite
find_package(SQLite3 REQUIRED)

include_directories(
    include
    include/database
    include/model
    include/repository
    include/service
    include/importer
    include/util
    include/validator
    include/app
)

add_executable(OceanNeedle
    src/main.cpp
    src/Database/Database.cpp
    src/Database/Statement.cpp

    src/model/Person.cpp
    src/model/Student.cpp
    src/model/Class.cpp
    src/model/Major.cpp
    src/model/College.cpp
    src/model/ImportRecord.cpp
    src/model/ImportDetail.cpp

    src/repository/PersonRepository.cpp
    src/repository/StudentRepository.cpp
    src/repository/ClassRepository.cpp
    src/repository/MajorRepository.cpp
    src/repository/CollegeRepository.cpp
    src/repository/ImportRecordRepository.cpp
    src/repository/ImportDetailRepository.cpp

    src/service/StudentService.cpp
    src/service/StudentImportService.cpp
    src/service/ImportService.cpp

    src/importer/StudentImporter.cpp

    src/util/CSVReader.cpp
    src/util/Confidence.cpp

    src/validator/StudentValidator.cpp

    src/app/ConsoleApp.cpp
)

target_link_libraries(OceanNeedle
    SQLite3::SQLite3
)