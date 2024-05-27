#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>

#include "Game.h"
#include "Item.h"

class Item;
class Game;
class Menu;

class Inventory {
    int size;
    std::string title;
    std::map<const int, Item *> items;

public:
    explicit Inventory(int size, const std::string &title);

    void setSize(int size);

    [[nodiscard]] int getSize() const;

    void setItem(int index, const Item *item);

    [[nodiscard]] Item *getItem(int index) const;

    virtual void show(Game *game);
    virtual void show(Game *game, button *backButton);

    virtual std::string getTitle() const;

    void showItemMenu(Game *game, int index, button* backButton);

    virtual ~Inventory() = default;
};
#endif
