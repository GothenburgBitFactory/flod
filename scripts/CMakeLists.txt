cmake_minimum_required (VERSION 2.8)

message ("-- Configuring scripts")

install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/prepare_builds DESTINATION bin)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/build_and_test DESTINATION bin)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/post-commit    DESTINATION bin)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/post-receive   DESTINATION bin)
