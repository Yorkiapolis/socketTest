cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_PREFIX_PATH install)

set(CMAKE_INSTALL_RPATH \$origin/../lib)

include_directories("include")
include_directories("threadutils/include")

add_subdirectory(threadutils)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    string(REPLACE ".c" "" name ${name})
    add_executable(${name} ${file})
    target_link_libraries(${name} pthread threadutils)

    install(TARGETS ${name}
            RUNTIME DESTINATION bin)
endforeach ()

