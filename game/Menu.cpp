#include "headers/Menu.h"

#include <unistd.h>

#include "../Console.h"
#include "headers/Player.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

int Menu::getKey() {
#ifdef _WIN32
    while (true) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                switch (ch) {
                    case 72:
                        return UP_KEY;
                    case 80:
                        return DOWN_KEY;
                    default:
                        return ch;
                }
            } else {
                if(ch == 13){
                    return ENTER_KEY;
                }
                return ch;
            }
        }
    }
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int result = 0;
    char ch;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        if (ch == '\033') {
            if (read(STDIN_FILENO, &ch, 1) > 0 && ch == '[') {
                if (read(STDIN_FILENO, &ch, 1) > 0) {
                    if (ch == 'A') {
                        result = UP_KEY;
                    } else if (ch == 'B') {
                        result = DOWN_KEY;
                    }
                }
            }
        }
    }

    if (ch == '\n') {
        result = ENTER_KEY;
    } else if (result == 0) {
        result = static_cast<unsigned char>(ch);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return result;
#endif
}

void Menu::show() {
    this->shown = true;
    bool exitMenu = false;

    do {
        clearConsole();

        for (int i = 0; i < this->elenents.size(); i++) {
            if (i == this->selectedButton) {
                if (!std::dynamic_pointer_cast<label>(this->elenents[this->selectedButton])) {
                    printFormattedString("<bg_grey><black> " + elenents[i]->text + " </black></bg_grey>");
                    continue;
                }
                this->selectedButton++;
            }
            printFormattedString(" " + this->elenents[i]->text + " ");
        }

        switch (getKey()) {
            case UP_KEY:
                if (this->selectedButton == 0) {
                    this->selectedButton = static_cast<int>(this->elenents.size()) - 1;
                } else {
                    this->selectedButton--;
                }
                break;
            case DOWN_KEY:
                if (this->selectedButton == static_cast<int>(this->elenents.size()) - 1) {
                    this->selectedButton = 0;
                } else {
                    this->selectedButton++;
                }
                break;
            case ENTER_KEY:
                if (const auto btnPtr = std::dynamic_pointer_cast<button>(this->elenents[this->selectedButton])) {
                    btnPtr->press();
                }
                exitMenu = true;
                break;
            default: ;
        }
    } while (!exitMenu);
}

void Menu::addContent(const std::shared_ptr<content> &element) {
    if (!this->shown) {
        this->elenents.push_back(element);
    }
}

Menu* mainMenu(Player *player) {
    const auto menu = new Menu();
    menu->addContent(std::make_shared<button>(
        "look for a room", [] {
        }
    ));
    menu->addContent(std::make_shared<button>(
        "restroom", [] {
        }
    ));
    menu->addContent(std::make_shared<button>(
        "inventory", [] {
        }
    ));
    return menu;
}