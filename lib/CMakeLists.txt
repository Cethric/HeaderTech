cmake_minimum_required(VERSION 3.19)
project(HeaderTechLibraries)

add_library(Example SHARED Sample.cpp Sample.hpp)

ConfigureLibrary(Example 0 0 1 "+dev")