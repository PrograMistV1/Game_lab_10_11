#include "headers/TreasureRoom.h"

#include <cstdlib>

#include "headers/Game.h"

Chest *OrdinaryRoom::getChest(Game *game) const {
    const int size = rand() % 5 + 1; //max 5, min 1
    const auto chest = new Chest(size, "<grey>Ordinary Chest</grey>");
    auto defaultItems = game->getItemFactory()->getDefaultItems();

    for (int i = 0; i < size; i++) {
        auto it = defaultItems.begin();
        std::advance(it, rand() % defaultItems.size());
        chest->setItem(i, it->second->clone());
    }
    return chest;
}

Chest *RareRoom::getChest(Game *game) const {
    const auto chest = new Chest(1, "<purple>Rare Chest</purple>");
    auto rareItems = game->getItemFactory()->getRareItems();

    auto it = rareItems.begin();
    std::advance(it, rand() % rareItems.size());
    chest->setItem(0, it->second->clone());
    return chest;
}

Chest::Chest(const int size, const std::string &title) : Inventory(size, title) {
}

void Chest::show(Game *game) {
    const std::function backButtonFunc = [game] {
        game->setMenu(mainMenu(game));
    };
    this->show(game, backButtonFunc);
}

void Chest::show(Game *game, std::function<void()> backButtonFunc) {
    const auto menu = new Menu();
    menu->addContent(new label{this->getTitle()});
    menu->addContent(new button{"close", backButtonFunc});

    menu->addContent(new button{
        "player inventory", [game, backButtonFunc, this] {
            std::function func = [this, game, backButtonFunc] {
                this->show(game, backButtonFunc);
            };
            game->getPlayer()->getInventory()->show(game, func);
        }
    });

    for (int index = 0; index < this->getSize(); index++) {
        Item *item = this->getItem(index);
        if (item != nullptr) {
            menu->addContent(new button{
                std::to_string(index + 1) + ": " + item->getDisplayName(), [game, item, this, index] {
                    game->setMenu(item->pickUpMenu(this, game->getPlayer()->getInventory(), index, game));
                }
            });
        } else {
            menu->addContent(new button{
                std::to_string(index + 1) + ": ", [] {
                }
            });
        }
    }
    game->setMenu(menu);
}
