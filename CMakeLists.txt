cmake_minimum_required(VERSION 3.18)
project(db-workshop)
set(CMAKE_CXX_STANDARD 17)

add_executable(01 src/01-connection-to-db.cpp)
add_executable(02 src/02-connection-via-environs.cpp)
add_executable(03 src/03-first-query.cpp)
add_executable(04 src/04-first-select.cpp)
add_executable(05 src/05-insert-and-transaction.cpp)
add_executable(06 src/06-exerc.cpp)

include_directories(src/models)
list(APPEND targets 01 02 03 04 05 06)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

foreach(target IN LISTS targets)
    target_link_libraries("${target}" pqxx PostgreSQL::PostgreSQL)
endforeach()