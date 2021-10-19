cmake_minimum_required(VERSION 3.20)
project(linknodeutils C)

set(CMAKE_C_STANDARD 11)

add_library(linknodeutils SHARED linknodeutils.c)

install(TARGETS linknodeutils
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)