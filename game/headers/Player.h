#ifndef PLAYER_H
#define PLAYER_H
#include "Inventory.h"

class Player {
    int maxHealth = 10;
    int health = maxHealth;

    int maxEnergy= 10;
    int energy = maxEnergy;
    Inventory *inventory = new Inventory(5);

public:
    [[nodiscard]] Inventory* getInventory() const;

    void save();
};

#endif
