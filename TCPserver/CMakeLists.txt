cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

include_directories("include")
include_directories("threadutils/include")

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    string(REPLACE ".c" "" name ${name})
    add_executable(${name} ${file} threadutils/tinycthread.c)
    target_link_libraries(${name} pthread)
endforeach ()

