cmake_minimum_required(VERSION 3.20)
project(Hash-Table-Implementation)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

# Fetch GoogleTest and set the timestamp to avoid policy warning
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)


include_directories(${CMAKE_SOURCE_DIR})

add_executable(Hash-Table-Implementation

        main.cpp
        Bottin.cpp
        ContratException.cpp
        TableHachage.hpp
        FoncteurHachage.hpp
        Bottin.cpp

)
enable_testing()
add_subdirectory(tests)
