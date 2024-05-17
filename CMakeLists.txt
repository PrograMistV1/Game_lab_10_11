cmake_minimum_required(VERSION 3.27.8)
project(Game_lab_10_11)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game_lab_10_11 main.cpp
        game/Console.h
        game/Console.cpp
        game/Game.cpp
        game/Game.h
        game/Player.cpp
        game/Player.h
        game/Inventory.cpp
        game/Inventory.h
        game/Item.cpp
        game/Item.h
        game/Menu.cpp
        game/Menu.h)
