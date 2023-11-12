cmake_minimum_required(VERSION 3.27)
project(Nexus C)

set(CMAKE_C_STANDARD 23)

add_executable(Nexus src/server.c
        src/server.c
        src/cman.c
        src/cman.h
        src/help_command.c
        src/help_command.h
        src/echo_command.c
        src/echo_command.h)
