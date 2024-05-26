#include "headers/TreasureRoom.h"

#include <cstdlib>

#include "headers/Game.h"

Inventory *ordinary_room::getChest(Game *game) const {
    const int size = rand() % 6 + 5;
    const auto inventory = new Inventory(size);
    auto defaultItems = game->getItemFactory()->getDefaultItems();

    auto it = defaultItems.begin();
    for (int i = 0; i < size; i++) {
        std::advance(it, rand() % defaultItems.size());
        inventory->setItem(i, it->second->clone());
    }
    return inventory;
}
