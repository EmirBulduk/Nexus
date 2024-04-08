cmake_minimum_required(VERSION 3.27)
project(Nexus C)

set(CMAKE_C_STANDARD 23)

add_executable(Nexus cnc/server.c
        cnc/server.c
        cnc/commands/cman.c
        cnc/commands/cman.h
        cnc/commands/help_command.c
        cnc/commands/help_command.h
        cnc/commands/echo_command.c
        cnc/commands/echo_command.h
        scanner/scanner.c
        scanner/scanner.h
        cnc/commands/bots_command.c
        cnc/commands/bots_command.h
        cnc/commands/Attack_command.c
        cnc/commands/Attack_command.h
        cnc/commands/attack/syn_command.c
        cnc/commands/attack/syn_command.h
        cnc/commands/info/ping_command.c
        cnc/commands/info/ping_command.h
        cnc/commands/info/whois.c
        cnc/commands/info/whois.h)
