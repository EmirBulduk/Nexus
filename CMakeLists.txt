cmake_minimum_required(VERSION 3.27)
project(Nexus C)

set(CMAKE_C_STANDARD 23)

add_executable(Nexus src/server.c
        src/server.c
        src/cman.c
        src/headers/cman.h
        src/commands/help_command.c
        src/headers/help_command.h
        src/commands/echo_command.c
        src/headers/echo_command.h)
