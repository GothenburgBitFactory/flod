cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/queue)

add_executable(queue Q.cpp       Q.h
                     create.cpp
                     queue.cpp
                     version.cpp)

install (TARGETS queue DESTINATION bin)

