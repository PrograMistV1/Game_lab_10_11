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
    /**
     * Initializes and starts the game
     */
    void init();

    ItemFactory *getItemFactory() const;

    Player *getPlayer() const;

    /**
     * Installs a new menu and deletes the previous menu object.
     * @param menu 
     */
    void setMenu(Menu *menu);
};

#endif
