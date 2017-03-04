cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}/src/libshared/src
                     ${FLOD_INCLUDE_DIRS})

set (flod_SRCS Q.cpp Q.h
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
               unhook.cpp
               utility.cpp
               version.cpp)

set (libshared_SRCS libshared/src/Args.cpp          libshared/src/Args.h
                    libshared/src/Color.cpp         libshared/src/Color.h
                    libshared/src/Configuration.cpp libshared/src/Configuration.h
                    libshared/src/FS.cpp            libshared/src/FS.h
                    libshared/src/JSON.cpp          libshared/src/JSON.h
                    libshared/src/Log.cpp           libshared/src/Log.h
                    libshared/src/Pig.cpp           libshared/src/Pig.h
                    libshared/src/Table.cpp         libshared/src/Table.h
                    libshared/src/format.cpp        libshared/src/format.h
                    libshared/src/shared.cpp        libshared/src/shared.h
                    libshared/src/unicode.cpp       libshared/src/unicode.h
                    libshared/src/utf8.cpp          libshared/src/utf8.h
                    libshared/src/wcwidth6.cpp)

add_library (central   STATIC ${flod_SRCS})
add_library (libshared STATIC ${libshared_SRCS})
add_executable (central_executable central.cpp central.h)

target_link_libraries (central_executable central libshared pthread ${FLOD_LIBRARIES})

set_property (TARGET central_executable PROPERTY OUTPUT_NAME "central")

install (TARGETS central_executable DESTINATION bin)

