#ifndef MENU_H
#define MENU_H

#include <functional>
#include <string>
#include <utility>

struct content {
    std::string text;

    content() = default;

    explicit content(std::string text) : text(std::move(text)) {
    }

    virtual ~content() = default;
};

struct label final : content {
    label() = default;

    explicit label(const std::string &text): content(text) {
    }
};

struct button final : content {
    std::function<void()> pressFunc;

    button() = default;

    button(const std::string &text, std::function<void()> func)
        : content(text), pressFunc(std::move(func)) {
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
    void addContent(content *element);

    void show();
};

Menu *startScreen(Game *game);

Menu *mainMenu(Game *game);

Menu *lookForRoom(Game *game);

#endif
