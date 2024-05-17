#ifndef MENU_H
#define MENU_H
#include <functional>
#include <string>
#include <vector>

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

    static std::string getKey();
public:
    Menu();
    explicit Menu(const std::vector<button>& buttons);

    void addButton(const button &button);

    void show();
};

#endif
