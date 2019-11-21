cmake_minimum_required(VERSION 3.10)
project(SEAL VERSION 1.0)
add_executable(homo homo.cpp)

find_package(SEAL)
target_link_libraries(homo SEAL::seal)
