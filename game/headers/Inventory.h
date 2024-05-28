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

    /**
     * Sets the inventory size.
     * @param size 
     */
    void setSize(int size);

    /**
     * Returns the inventory size.
     */
    [[nodiscard]] int getSize() const;

    /**
    * Places a clone of an item in an inventory slot.
    * The transmitted object is then destroyed.
     * @param index
     * @param item
     */
    void setItem(int index, const Item *item);

    /**
     * Returns a clone of the item in the inventory slot.
     * @param index
     * @return
     */
    [[nodiscard]] Item *getItem(int index) const;

    /**
     * Shows inventory menu.
     * @param game 
     */
    virtual void show(Game *game);

    /**
     * Does the same thing as @link show(Game *game), but also sets a custom function for the back button.
     * @param game
     * @param backButtonFunc
     */
    virtual void show(Game *game, std::function<void()> backButtonFunc);

    /**
     * Returns the inventory title
     */
    virtual std::string getTitle() const;

    /**
     * Shows the action menu of an item in a specific inventory slot.
     * @param game
     * @param index
     * @param backButtonFunc
     */
    void showItemMenu(Game *game, int index, std::function<void()> backButtonFunc);

    virtual ~Inventory() = default;
};
#endif
