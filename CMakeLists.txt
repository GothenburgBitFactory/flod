cmake_minimum_required (VERSION 2.8)
set (CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set (HAVE_CMAKE true)

project (flod)
include (CXXSniffer)
include (ExternalProject)

set (PROJECT_VERSION "2.0.0")

set (PACKAGE "${PROJECT_NAME}")
set (VERSION "${PROJECT_VERSION}")
set (PACKAGE_BUGREPORT "support@taskwarrior.org")
set (PACKAGE_NAME "${PACKAGE}")
set (PACKAGE_TARNAME "${PACKAGE}")
set (PACKAGE_VERSION "${VERSION}")
set (PACKAGE_STRING "${PACKAGE} ${VERSION}")

if (FREEBSD)
SET (FLOD_MAN1DIR man/man1 CACHE STRING "Installation directory for man pages, section 1")
SET (FLOD_MAN5DIR man/man5 CACHE STRING "Installation directory for man pages, section 5")
else (FREEBSD)
SET (FLOD_MAN1DIR share/man/man1 CACHE STRING "Installation directory for man pages, section 1")
SET (FLOD_MAN5DIR share/man/man5 CACHE STRING "Installation directory for man pages, section 5")
endif (FREEBSD)
SET (FLOD_DOCDIR  share/doc/flod CACHE STRING "Installation directory for doc files")

message ("-- Looking for pthread")
find_path (PTHREAD_INCLUDE_DIR pthread.h)
find_library (PTHREAD_LIBRARY NAMES pthread)
if (PTHREAD_INCLUDE_DIR AND PTHREAD_LIBRARY)
  message ("-- Found pthread: ${PTHREAD_LIBRARY}")
  set (HAVE_LIBPTHREAD true)
  set (FLOD_INCLUDE_DIRS ${FLOD_INCLUDE_DIRS} ${PTHREAD_INCLUDE_DIR})
  set (FLOD_LIBRARIES    ${FLOD_LIBRARIES}    ${PTHREAD_LIBRARIES})
endif (PTHREAD_INCLUDE_DIR AND PTHREAD_LIBRARY)

message ("-- Configuring cmake.h")
configure_file (
  ${CMAKE_SOURCE_DIR}/cmake.h.in
  ${CMAKE_SOURCE_DIR}/cmake.h)

add_subdirectory (src)
add_subdirectory (scripts)
add_subdirectory (doc)
if (EXISTS ${CMAKE_SOURCE_DIR}/test)
  add_subdirectory (test EXCLUDE_FROM_ALL)
endif (EXISTS ${CMAKE_SOURCE_DIR}/test)

set (doc_FILES ChangeLog AUTHORS COPYING)
foreach (doc_FILE ${doc_FILES})
  install (FILES ${doc_FILE} DESTINATION ${FLOD_DOCDIR})
endforeach (doc_FILE)

# ---

set (CPACK_SOURCE_GENERATOR "TGZ")
set (CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_NAME}-${PACKAGE_VERSION})
set (CPACK_SOURCE_IGNORE_FILES  "CMakeCache" "CMakeFiles" "CPackConfig" "CPackSourceConfig"
                                "_CPack_Packages" "cmake_install" "install_manifest"
                                "Makefile$" "/\\\\.gitignore" "/\\\\.git/" "swp$")
include (CPack)
