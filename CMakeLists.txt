cmake_minimum_required(VERSION 2.8)
project (PizzaSlice)

SET(CMAKE_CXX_FLAGS "-std=c++0x -pthread -lboost_system -lmariadbclient")

include_directories (${CMAKE_SOURCE_DIR}/src/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")
find_package(MariaDB REQUIRED)
include_directories (${MARIADB_INCLUDE_DIR})


file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory (src)


