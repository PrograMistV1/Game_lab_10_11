#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>

#include "Player.h"

class Player;
class Inventory;
class Menu;
class Game;

class Item {
    int count = 1;
    const std::string id;

public:
    Item() = default;

    explicit Item(const Item *item);

    void setCount(int count);

    [[nodiscard]] int getCount() const;

    virtual std::string getId() const = 0;

    virtual Item *clone() const = 0;

    virtual void use(Player *player) const = 0;

    virtual std::string getDisplayName() const = 0;

    virtual ~Item() = default;

    Menu *pickUpMenu(Inventory *inventory, int index, Game *game);
};

class ItemFactory {
    std::map<std::string, Item *> defaultItems;
    std::map<std::string, Item *> rareItems;

public:
    void registerDefaultItem(const Item *item);

    std::map<std::string, Item *> getDefaultItems();

    std::map<std::string, Item *> getRareItems();
};

class Gold : public Item {
public:
    Gold() = default;

    explicit Gold(const Gold *gold);

    std::string getId() const override;

    Item *clone() const override;

    void use(Player *player) const override;

    std::string getDisplayName() const override;
};

#endif
