#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"

class Inventory;

class Player {
    int maxHealth = 10;
    int health = maxHealth;

    int maxEnergy = 10;
    int energy = maxEnergy;
    Inventory *inventory;

public:
    Player();

    [[nodiscard]] Inventory *getInventory() const;

    void save();

    [[nodiscard]] int getHealth() const;

    [[nodiscard]] int getMaxHealth() const;

    void setHealth(int health);

    void setMaxHealth(int health);

    [[nodiscard]] int getEnergy() const;

    [[nodiscard]] int getMaxEnergy() const;

    void setEnergy(int energy);

    void setMaxEnergy(int energy);
};

#endif
