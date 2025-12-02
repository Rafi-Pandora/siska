cmake_minimum_required(VERSION 3.10)
project(SISKA)

# Ambil semua file .cpp dan .h di direktori root
file(GLOB SOURCES
    "*.cpp"
    "*.h"
)

add_executable(SISKA ${SOURCES})
