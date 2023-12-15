cmake_minimum_required(VERSION 3.26)
project(NSock)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Lib)
add_subdirectory(Utils)

add_executable(NSockServer Server.cpp)
add_executable(NSockClient Client.cpp)

target_link_libraries(NSockServer PUBLIC Socket Utils)
target_link_libraries(NSockClient PUBLIC Socket Utils)