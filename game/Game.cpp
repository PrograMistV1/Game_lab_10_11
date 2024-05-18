#include "headers/Game.h"
#include <filesystem>
#include <iostream>

#include "headers/Menu.h"

namespace fs = std::filesystem;

void Game::init() {
    const auto menu = new Menu();
    menu->addContent(std::make_shared<label>("game (lab 10-11)"));
    menu->addContent(std::make_shared<button>(
        "start", [this] {
            this->start();
        }
    ));
    menu->addContent(std::make_shared<button>(
        "load", [] {
            std::cout << "load pressed" << std::endl;
        }
    ));
    menu->addContent(std::make_shared<button>(
        "exit", [this] {
            this->setMenu(nullptr);
            std::cout << "Closing the game..." << std::endl;
        }
    ));
    this->nextMenu = menu;

    while (this->nextMenu != nullptr) {
        this->nextMenu->show();
    }
}

void Game::start() {
    this->player = new Player();
    this->setMenu(mainMenu(this->player));
}

void Game::load() {
    fs::create_directory("./saves");
    this->player = new Player;
}

void Game::setMenu(Menu *menu) {
    delete this->nextMenu;
    this->nextMenu = menu;
}

