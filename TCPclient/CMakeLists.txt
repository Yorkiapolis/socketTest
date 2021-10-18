cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_INSTALL_PREFIX install)

set(CMAKE_INSTALL_RPATH \$ORIGIN/../lib)

include_directories("include")

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    string(REPLACE ".c" "" name ${name})
    add_executable(${name} ${file})

    install(TARGETS ${name}
            RUNTIME DESTINATION bin)
endforeach ()

