cmake_minimum_required(VERSION 3.28)
project(Lab10_Gra_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab10_Gra_ main.cpp
        game/Console.h
        game/Console.cpp
        game/Game.cpp
        game/Game.h
        game/Player.cpp
        game/Player.h
        game/Inventory.cpp
        game/Inventory.h
        game/Item.cpp
        game/Item.h)
