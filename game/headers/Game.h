#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Player.h"

class Player;
class ItemFactory;

class Game {
    Player *player = nullptr;

    Menu *currentMenu = nullptr;

    ItemFactory *factory = nullptr;

public:
    void init();

    ItemFactory *getItemFactory() const;

    Player *getPlayer() const;

    void setMenu(Menu *menu);
};

#endif
