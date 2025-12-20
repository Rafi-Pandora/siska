cmake_minimum_required(VERSION 3.10)

# Project name
project(SISKA)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source directories
set(CORE_DIR "${PROJECT_SOURCE_DIR}/src/core")
set(DB_DIR "${PROJECT_SOURCE_DIR}/src/db")
set(GUI_DIR  "${PROJECT_SOURCE_DIR}/src/gui")
set(SRC_DIR  "${PROJECT_SOURCE_DIR}/src")

# Include header directories
include_directories(
    ${CORE_DIR}
    ${GUI_DIR}
    ${SRC_DIR}
    ${DB_DIR}
    )

# Source files
set(SOURCES
    ${CORE_DIR}/railwayMLL.cpp
    ${DB_DIR}/DatabaseManager.cpp
    ${SRC_DIR}/main.cpp
)

# Build executable
add_executable(SISKA ${SOURCES})

target_link_libraries(SISKA sqlite3)