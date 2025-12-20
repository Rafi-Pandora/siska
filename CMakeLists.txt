cmake_minimum_required(VERSION 3.10)
project(SISKA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_DIR "${PROJECT_SOURCE_DIR}/src/core")
set(DB_DIR   "${PROJECT_SOURCE_DIR}/src/db")
set(SRC_DIR  "${PROJECT_SOURCE_DIR}/src")

add_executable(SISKA
    ${CORE_DIR}/railwayMLL.cpp
    ${DB_DIR}/DatabaseManager.cpp
    ${SRC_DIR}/main.cpp
)

target_include_directories(SISKA PRIVATE
    ${CORE_DIR}
    ${DB_DIR}
    ${SRC_DIR}
)

target_compile_definitions(SISKA PRIVATE
    DB_PATH="${PROJECT_SOURCE_DIR}/data/railway.db"
)

find_package(SQLite3 REQUIRED)
target_link_libraries(SISKA SQLite::SQLite3)
