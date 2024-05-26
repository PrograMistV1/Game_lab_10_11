#include "headers/Game.h"
#include <filesystem>

#include "headers/Menu.h"

namespace fs = std::filesystem;

void registerItems(ItemFactory *factory);

void Game::init() {
    factory = new ItemFactory();
    registerItems(this->factory);

    this->setMenu(startScreen(this));

    while (this->nextMenu != nullptr) {
        this->nextMenu->show();
    }
}

void Game::start() {
    this->player = new Player();
    this->setMenu(mainMenu(this));
}

void Game::load() {
    fs::create_directory("./saves");
    this->player = new Player;
}

ItemFactory *Game::getItemFactory() const {
    return factory;
}


Player *Game::getPlayer() const {
    return this->player;
}

void Game::setMenu(Menu *menu) {
    delete this->nextMenu;
    this->nextMenu = menu;
}

void registerItems(ItemFactory *factory) {
    factory->registerDefaultItem(new Gold());
}
