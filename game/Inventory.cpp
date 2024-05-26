#include "headers/Inventory.h"

Inventory::Inventory(const int size) : size(size) {
}

void Inventory::setSize(const int size) {
    this->size = size;
}

int Inventory::getSize() const {
    return this->size;
}

void Inventory::setItem(const int index, const Item *item) {
    if (index >= 0 && index < this->size) {
        if (this->getItem(index) != nullptr) {
            delete this->items[index];
            this->items.erase(index);
        }
        if (item != nullptr) {
            this->items[index] = item->clone();
        }
    }
}

Item *Inventory::getItem(const int index) const {
    const auto it = this->items.find(index);
    if (it != this->items.end()) {
        return it->second->clone();
    }
    return nullptr;
}

void Inventory::show(Game *game) {
    auto menu = new Menu();
    menu->addContent(new button{
        "back", [game] {
            game->setMenu(mainMenu(game));
        }
    });

    for (int index = 0; index < this->getSize(); index++) {
        Item *item = this->getItem(index);
        if (item != nullptr) {
            menu->addContent(new button{
                std::to_string(index + 1) + ": " + item->getDisplayName(), [game, item, this, index] {
                    game->setMenu(item->pickUpMenu(this, index, game));
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
