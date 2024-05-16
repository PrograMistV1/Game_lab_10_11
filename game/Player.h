#ifndef PLAYER_H
#define PLAYER_H
#include "Inventory.h"

class Player {
    Inventory *inventory = new Inventory(5);

public:
    [[nodiscard]] Inventory* getInventory() const;
};

#endif
