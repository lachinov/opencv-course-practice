cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

set(PRJ_NAME "lab1")

project(${PRJ_NAME})
add_executable( ${PRJ_NAME} main.cpp )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${PRJ_NAME} ${OpenCV_LIBS} )
install (TARGETS ${PRJ_NAME} DESTINATION install)

ADD_CUSTOM_COMMAND(TARGET ${PRJ_NAME}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/road.png ${CMAKE_CURRENT_BINARY_DIR}
)