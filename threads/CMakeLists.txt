cmake_minimum_required (VERSION 2.8.11)
project(threads)
set (CMAKE_CXX_STANDARD 11)

find_package(Threads)

add_executable(example1 src/threads_example1.cpp)
target_link_libraries(example1 ${CMAKE_THREAD_LIBS_INIT})

