#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Player.h"

class Game {
    Player *player = nullptr;

    Menu *nextMenu = nullptr;
public:
    void init();
    void start();
    void load();

    void setMenu(Menu *menu);
};

#endif
