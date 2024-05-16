#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    Player *player = nullptr;
public:
    void start();
    void load();
};

#endif
