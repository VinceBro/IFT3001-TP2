cmake_minimum_required(VERSION 3.17)
project(question4)

set(CMAKE_CXX_STANDARD 14)
add_executable(question4 tests.cpp jeu.cpp monstre.cpp jeu.hpp monstre.hpp tableau.hpp)