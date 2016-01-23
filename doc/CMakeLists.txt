cmake_minimum_required (VERSION 2.8)

message ("-- Configuring man pages")

configure_file (man/flod.1.in   man/flod.1)
configure_file (man/flodrc.5.in man/flodrc.5)

install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/ DESTINATION ${FLOD_MAN1DIR} FILES_MATCHING PATTERN "*.1")
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/ DESTINATION ${FLOD_MAN5DIR} FILES_MATCHING PATTERN "*.5")

