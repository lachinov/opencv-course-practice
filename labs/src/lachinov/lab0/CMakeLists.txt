cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

set(PRJ_NAME "lab0")

project(${PRJ_NAME})
add_executable( ${PRJ_NAME} main.cpp )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${PRJ_NAME} ${OpenCV_LIBS} )
install (TARGETS ${PRJ_NAME} DESTINATION install)