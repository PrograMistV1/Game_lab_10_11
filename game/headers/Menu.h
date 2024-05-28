#ifndef MENU_H
#define MENU_H

#include <functional>
#include <string>
#include <utility>

struct content {
    std::string text;

    explicit content(const std::string &text) : text(std::move(text)) {
    }

    virtual ~content() = default;
};

struct label final : content {
    explicit label(const std::string &text): content(text) {
    }
};

struct button final : content {
    std::function<void()> pressFunc;

    button(const std::string &text, std::function<void()> func)
        : content(text), pressFunc(std::move(func)) {
    }

    button *clone() const {
        return new button(text, pressFunc);
    }

    void press() const {
        this->pressFunc();
    }
};

#include <vector>

#include "Game.h"

#define UP_KEY 1000
#define DOWN_KEY 1001
#define ENTER_KEY 1002

class Game;

class Menu {
    std::vector<content *> elenents;
    int selectedButton = 0;

    bool shown = false;

    static int getKey();

public:
    /**
     * Displays a menu in the console.
     * @param element
     */
    void addContent(content *element);

    void show();

    ~Menu();
};

/**
 * Creates the main menu of the game.
 * @param game
 * @return
 */
Menu *mainMenu(Game *game);

/**
 * Creates a room search menu.
 * @param game
 * @return
 */
Menu *lookForRoom(Game *game);

#endif
