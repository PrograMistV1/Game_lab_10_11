#ifndef MENU_H
#define MENU_H
#include "Player.h"
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define UP_KEY 1000
#define DOWN_KEY 1001
#define ENTER_KEY 1002

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

class Menu {
    std::vector<std::shared_ptr<content>> elenents;
    int selectedButton = 0;

    bool shown = false;

    static int getKey();

public:
    void addContent(const std::shared_ptr<content> &element);

    void show();
};

Menu* mainMenu(Player *player);

#endif
