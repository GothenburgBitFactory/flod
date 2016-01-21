cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${FLOD_INCLUDE_DIRS})

set (flod_SRCS Args.cpp          Args.h
               Configuration.cpp Configuration.h
               Q.cpp             Q.h
               clear.cpp
               config.cpp
               create.cpp
               destroy.cpp
               help.cpp
               hook.cpp
               info.cpp
               post.cpp
               process.cpp
               stats.cpp
               unhook.cpp
               version.cpp)

add_library (queue STATIC ${flod_SRCS})
include_directories(${CMAKE_INSTALL_PREFIX}/include)
link_directories(${CMAKE_INSTALL_PREFIX}/lib)
add_executable (queue_executable queue.cpp)

target_link_libraries (queue_executable queue common ${FLOD_LIBRARIES})

set_property (TARGET queue_executable PROPERTY OUTPUT_NAME "queue")

install (TARGETS queue_executable DESTINATION bin)

