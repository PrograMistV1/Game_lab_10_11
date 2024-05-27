#ifndef TREASUREROOM_H
#define TREASUREROOM_H

#include "Inventory.h"

class Chest;

class TreasureRoom {
public:
    virtual Chest *getChest(Game *game) const = 0;

    virtual ~TreasureRoom() = default;
};

class OrdinaryRoom final : public TreasureRoom {
public:
    Chest *getChest(Game *game) const override;
};

class RareRoom final : public TreasureRoom {
public:
    Chest *getChest(Game *game) const override;
};

class Chest final : public Inventory {
public:
    explicit Chest(int size, const std::string &title);

    void show(Game *game) override;

    void show(Game *game, button *backButton) override;
};

#endif
