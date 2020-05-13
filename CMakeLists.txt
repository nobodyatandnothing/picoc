cmake_minimum_required(VERSION 3.15)
project(picoc C)

execute_process(COMMAND git show-ref --abbrev=8 --head --hash head OUTPUT_VARIABLE hash OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND git describe --abbrev=0 --tags OUTPUT_VARIABLE tag OUTPUT_STRIP_TRAILING_WHITESPACE)
message("${tag} ${hash}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
set(CMAKE_REQUIRED_LIBRARIES m readline)
add_definitions(-DUNIX_HOST -DVER="${hash}" -DTAG="${tag}")
#add_definitions(-DDEBUG_EXPRESSIONS)

include_directories(.)

add_executable(picoc
        cstdlib/ctype.c
        cstdlib/errno.c
        cstdlib/math.c
        cstdlib/stdbool.c
        cstdlib/stdio.c
        cstdlib/stdlib.c
        cstdlib/string.c
        cstdlib/time.c
        cstdlib/unistd.c
        platform/library_unix.c
        platform/platform_unix.c
        clibrary.c
        debug.c
        expression.c
        heap.c
        include.c
        interpreter.h
        lex.c
        parse.c
        picoc.c
        picoc.h
        platform.c
        platform.h
        table.c
        type.c
        variable.c)

target_link_libraries(picoc -lm -lreadline)
