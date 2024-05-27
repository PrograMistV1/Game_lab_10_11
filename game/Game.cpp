#include "headers/Game.h"
#include <filesystem>

#include "headers/Menu.h"

namespace fs = std::filesystem;

void registerItems(ItemFactory *factory);

void Game::init() {
    factory = new ItemFactory();
    registerItems(this->factory);

    this->player = new Player();
    this->setMenu(mainMenu(this));

    while (this->currentMenu != nullptr) {
        this->currentMenu->show();
    }
}

ItemFactory *Game::getItemFactory() const {
    return factory;
}

Player *Game::getPlayer() const {
    return this->player;
}

void Game::setMenu(Menu *menu) {
    delete this->currentMenu;
    this->currentMenu = menu;
}

void registerItems(ItemFactory *factory) {
    factory->registerDefaultItem(new Gold());
    factory->registerDefaultItem(new Bread());
    factory->registerDefaultItem(new Rock());

    factory->registerRareItem(new HealthPotion());
}
