cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${FLOD_INCLUDE_DIRS})

set (flod_SRCS Q.cpp             Q.h
               clear.cpp
               config.cpp
               create.cpp
               destroy.cpp
               help.cpp
               hook.cpp
               info.cpp
               post.cpp
               process.cpp
               retry.cpp
               stats.cpp
               unhook.cpp
               utility.cpp
               version.cpp)

add_library (central STATIC ${flod_SRCS})
include_directories(${CMAKE_INSTALL_PREFIX}/include)
link_directories(${CMAKE_INSTALL_PREFIX}/lib)
add_executable (central_executable central.cpp central.h)

target_link_libraries (central_executable central common ${FLOD_LIBRARIES})

set_property (TARGET central_executable PROPERTY OUTPUT_NAME "central")

install (TARGETS central_executable DESTINATION bin)

