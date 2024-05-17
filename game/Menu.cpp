#include "Menu.h"
#include "Console.h"

#include <thread>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

Menu::Menu() = default;

Menu::Menu(const std::vector<button> &buttons) : buttons(buttons) {
}

std::string Menu::getKey() {
#ifdef _WIN32
    for (char c = 8; c <= 222; c++) {
        if (GetAsyncKeyState(c) & 0x8000) {
            std::cout << c << endl;
            return c;
        }
    }
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == '\033') {
            if (read(STDIN_FILENO, &ch, 1) > 0 && ch == '[') {
                if (read(STDIN_FILENO, &ch, 1) > 0) {
                    return "\033[" + std::string(1, ch);
                }
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return std::basic_string(1, ch);
#endif
}

void Menu::show() {
    bool exitMenu = false;

    do {
        clearConsole();

        for (int i = 0; i < this->buttons.size(); i++) {
            if (i == this->selectedButton) {
                printFormattedString("<bg_grey><black> " + buttons[i].text + " </black></bg_grey>");
            } else {
                printFormattedString(" " + this->buttons[i].text + " ");
            }
        }

        const std::string key = getKey();
        if (key == "\033[A") {
            if (this->selectedButton == 0) {
                this->selectedButton = static_cast<int>(this->buttons.size()) - 1;
            } else {
                this->selectedButton--;
            }
        } else if (key == "\033[B") {
            if (this->selectedButton == static_cast<int>(this->buttons.size()) - 1) {
                this->selectedButton = 0;
            } else {
                this->selectedButton++;
            }
        } else if (key == "\n") {
            buttons[selectedButton].press();
            exitMenu = true;
        }
    } while (!exitMenu);
}

void Menu::addButton(const button &button) {
    this->buttons.push_back(button);
}
