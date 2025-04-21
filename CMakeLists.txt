cmake_minimum_required(VERSION 3.31)
project(World_Sim_Cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(World_Sim_Cpp
        main.cpp
        Organism.cpp
        Organism.h
        World.cpp
        World.h
        Animal.cpp
        Animal.h
        Wolf.cpp
        Wolf.h
        Sheep.cpp
        Sheep.h
)

find_package(Curses REQUIRED)
target_link_libraries(World_Sim_Cpp ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIRS})
