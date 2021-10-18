cmake_minimum_required(VERSION 3.10.2)
project(threadutils C)

set(CMAKE_C_STANDARD 99)

add_library(threadutils SHARED tinycthread.c)
target_link_libraries(threadutils pthread)

install(TARGETS threadutils
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)