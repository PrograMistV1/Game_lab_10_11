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

    virtual void use(Game* game, int slot, button* backButton) const = 0;

    virtual std::string getDisplayName() const = 0;

    virtual std::string getInfo() const = 0;

    virtual ~Item() = default;

    Menu *pickUpMenu(Inventory *from, Inventory *to, int index, Game *game);
};

class ItemFactory {
    std::map<std::string, Item *> defaultItems;
    std::map<std::string, Item *> rareItems;

public:
    void registerDefaultItem(const Item *item);
    void registerRareItem(const Item *item);

    std::map<std::string, Item *> getDefaultItems();

    std::map<std::string, Item *> getRareItems();
};

class Gold final : public Item {
public:
    Gold() = default;

    explicit Gold(const Gold *gold);

    std::string getId() const override;

    Item *clone() const override;

    void use(Game* game, int slot, button* backButton) const override;

    std::string getDisplayName() const override;

    std::string getInfo() const override;
};

class Bread final : public Item {
public:
    Bread() = default;

    explicit Bread(const Bread *bread);

    std::string getId() const override;

    Item *clone() const override;

    void use(Game* game, int slot, button* backButton) const override;

    std::string getDisplayName() const override;

    std::string getInfo() const override;
};

class Rock final : public Item {
public:
    Rock() = default;

    explicit Rock(const Rock *rock);

    std::string getId() const override;

    Item *clone() const override;

    void use(Game* game, int slot, button* backButton) const override;

    std::string getDisplayName() const override;

    std::string getInfo() const override;
};

class HealthPotion final : public Item {
public:
    HealthPotion() = default;

    explicit HealthPotion(const HealthPotion *healtPotion);

    std::string getId() const override;

    Item *clone() const override;

    void use(Game* game, int slot, button* backButton) const override;

    std::string getDisplayName() const override;

    std::string getInfo() const override;
};
#endif
