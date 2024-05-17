#include "Game.h"
#include <filesystem>
#include <iostream>

#include "Menu.h"

namespace fs = std::filesystem;

void Game::init() {
    auto menu = new Menu();
    menu->addButton({
        "start", [menu] {
            std::cout << "start pressed" << std::endl;
        }
    });
    menu->addButton({
        "load", [menu] {
            std::cout << "load pressed" << std::endl;
        }
    });
    menu->addButton({
        "exit", [] {
            std::cout << "Closing the game..." << std::endl;
        }
    });
    menu->show();
}


void Game::load() {
    fs::create_directory("./saves");
    this->player = new Player;
}
