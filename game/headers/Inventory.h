#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>

#include "Game.h"
#include "Item.h"

class Item;
class Game;
class Menu;

class Inventory {
    int size = 0;
    std::map<const int, Item *> items;

public:
    explicit Inventory(int size);

    void setSize(int size);

    [[nodiscard]] int getSize() const;

    void setItem(int index, const Item *item);

    [[nodiscard]] Item *getItem(int index) const;

    void show(Game *game);
};
#endif
