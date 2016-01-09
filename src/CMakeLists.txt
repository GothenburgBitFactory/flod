cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/queue)

add_executable(queue Q.cpp       Q.h
                     clear.cpp
                     config.cpp
                     create.cpp
                     destroy.cpp
                     help.cpp
                     hook.cpp
                     info.cpp
                     post.cpp
                     process.cpp
                     queue.cpp
                     stats.cpp
                     unhook.cpp
                     version.cpp)

install (TARGETS queue DESTINATION bin)

