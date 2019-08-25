cmake_minimum_required(VERSION 3.12)
project(parties C)

set(CMAKE_C_STANDARD 99)
link_directories(.)
add_executable(parties main.c member.c member.h set.h list.h party.c party.h)
target_link_libraries(parties libmtm.a)
set(CMAKE_C_FLAGS
        "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")