cmake_minimum_required(VERSION 3.27)
project(Nexus C)

set(CMAKE_C_STANDARD 23)

add_executable(Nexus src/main.c
        src/main.c
        src/cman.c
        src/headers/cman.h
        commands/help_command.c
        commands/headers/help_command.h
        commands/echo_command.c
        commands/headers/echo_command.h)
