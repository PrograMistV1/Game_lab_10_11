#ifndef MENU_H
#define MENU_H
#include <functional>
#include <string>
#include <vector>

#define UP_KEY 1000
#define DOWN_KEY 1001
#define ENTER_KEY 1002

struct button {
    std::string text;
    std::function<void()> pressFunc;

    void press() const {
        this->pressFunc();
    }
};

class Menu {
    std::vector<button> buttons;
    int selectedButton = 0;

    static int getKey();
public:
    Menu();
    explicit Menu(const std::vector<button>& buttons);

    void addButton(const button &button);

    void show();
};

#endif
