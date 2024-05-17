cmake_minimum_required(VERSION 3.27.8)
project(Game_lab_10_11)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game_lab_10_11 main.cpp
        Console.h
        Console.cpp
        game/Game.cpp
        game/headers/Game.h
        game/Player.cpp
        game/headers/Player.h
        game/Inventory.cpp
        game/headers/Inventory.h
        game/Item.cpp
        game/headers/Item.h
        game/Menu.cpp
        game/headers/Menu.h)
