cmake_minimum_required (VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

project (flod)
set (PROJECT_VERSION "1.1.0")

message ("CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")

include (CheckCXXCompilerFlag)

# NOTE: If we are to actually use C++11 features, we should either require
#       a compiler that supports the -std=c++11 flag or check for the
#       features used.
#       Relying on -std=c++0x or even -std=gnu++0x is highly volatile.

CHECK_CXX_COMPILER_FLAG("-std=c++11" _HAS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" _HAS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=gnu++0x" _HAS_GNU0X)

if (_HAS_CXX11)
  set (_CXX11_FLAGS "-std=c++11")
elseif (_HAS_CXX0X)
  message (WARNING "Enabling -std=c++0x draft compile flag. Your compiler does not support the standard '-std=c++11' option.  Consider upgrading.")
  set (_CXX11_FLAGS "-std=c++0x")
elseif (_HAS_GNU0X)
  message (WARNING "Enabling -std=gnu++0x draft compile flag. Your compiler does not support the standard '-std=c++11' option. Consider upgrading.")
  set (_CXX11_FLAGS "-std=gnu++0x")
else (_HAS_CXX11)
 message (FATAL_ERROR "C++11 support missing. Try upgrading your C++ compiler. If you have a good reason for using an outdated compiler, please let us know at support@tasktools.org.")
endif (_HAS_CXX11)

SET (FLOD_MAN3DIR share/man/man1 CACHE STRING "Installation directory for man pages, section 1")
SET (FLOD_LIBDIR  lib            CACHE STRING "Installation directory for the library")
SET (FLOD_DOCDIR  share/doc/flod CACHE STRING "Installation directory for doc files")

set (CMAKE_CXX_FLAGS "${_CXX11_FLAGS} ${CMAKE_CXX_FLAGS}")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Wsign-compare -Wreturn-type ${CMAKE_CXX_FLAGS}")

set (PACKAGE "${PROJECT_NAME}")
set (VERSION "${PROJECT_VERSION}")
set (PACKAGE_BUGREPORT "support@taskwarrior.org")
set (PACKAGE_NAME "${PACKAGE}")
set (PACKAGE_TARNAME "${PACKAGE}")
set (PACKAGE_VERSION "${VERSION}")
set (PACKAGE_STRING "${PACKAGE} ${VERSION}")

add_subdirectory (src)

set (doc_FILES ChangeLog AUTHORS COPYING)
foreach (doc_FILE ${doc_FILES})
  install (FILES ${doc_FILE}  DESTINATION ${FLOD_DOCDIR})
endforeach (doc_FILE)

# ---

set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_NAME}-${PACKAGE_VERSION})
set (CPACK_SOURCE_IGNORE_FILES  "CMakeCache" "CMakeFiles" "CPackConfig" "CPackSourceConfig"
                                "_CPack_Packages" "cmake_install" "install_manifest"
                                "Makefile$"
                                "/\\\\.gitignore" "/\\\\.git/" "swp$")
include (CPack)
