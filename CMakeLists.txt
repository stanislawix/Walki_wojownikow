cmake_minimum_required(VERSION 3.20)
project(Walki_wojownikow)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Walki_wojownikow
        Mag.cpp
        Mag.h
        main.cpp
        Polimorf.cpp
        Polimorf.h
        Rycerz.cpp
        Rycerz.h
        Skill.cpp
        Skill.h
        Wojownik.cpp
        Wojownik.h)
