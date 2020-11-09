cmake_minimum_required(VERSION 2.8)
project(vertex-cover)

if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
  add_subdirectory(minisat)
else()
  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()

## Project specific configurations goes here

# enable c++11 support
# set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread -g${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*, -fuchsia-default-arguments, -google-runtime-references")

# create the main executable
# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)
## add additional .cpp files if needed
add_executable(vertex-cover-prj vertex-cover-proj.cpp parse_line.cpp graph.cpp)
# link minisat library with the main executable
target_link_libraries(vertex-cover-prj minisat-lib-static)





