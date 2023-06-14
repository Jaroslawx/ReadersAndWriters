cmake_minimum_required(VERSION 3.24.1)
project(ReadersAndWriters)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)

add_executable(ReadersAndWriters main.cpp first_solution.h second_solution.h third_solution.h)
target_link_libraries(ReadersAndWriters PRIVATE Threads::Threads)
