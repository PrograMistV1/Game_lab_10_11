#ifndef TREASUREROOM_H
#define TREASUREROOM_H

#include "Inventory.h"

class treasure_room {
public:
    virtual Inventory *getChest(Game *game) const = 0;

    virtual ~treasure_room() = default;
};

class ordinary_room : public treasure_room {
public:
    Inventory *getChest(Game *game) const override;
};

#endif
