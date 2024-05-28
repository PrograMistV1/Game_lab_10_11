#include "headers/Menu.h"

#include "../Console.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/TreasureRoom.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
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
                if (typeid(*this->elenents[this->selectedButton]) != typeid(label)) {
                    printFormattedString("<bg_grey><black> " + elenents[i]->text + " </black></bg_grey>");
                    continue;
                }
                this->selectedButton++;
            }
            printFormattedString(" " + this->elenents[i]->text + " ");
        }

        switch (getKey()) {
            case UP_KEY:
                do {
                    if (this->selectedButton == 0) {
                        this->selectedButton = static_cast<int>(this->elenents.size()) - 1;
                    } else {
                        this->selectedButton--;
                    }
                } while (typeid(*this->elenents[this->selectedButton]) == typeid(label));
                break;
            case DOWN_KEY:
                if (this->selectedButton == static_cast<int>(this->elenents.size()) - 1) {
                    this->selectedButton = 0;
                } else {
                    this->selectedButton++;
                }
                break;
            case ENTER_KEY:
                if (typeid(*this->elenents[this->selectedButton]) == typeid(button)) {
                    static_cast<button *>(this->elenents[this->selectedButton])->press();
                }
                exitMenu = true;
                break;
            default: ;
        }
    } while (!exitMenu);
}

void Menu::addContent(content *element) {
    if (!this->shown) {
        this->elenents.push_back(element);
    }
}

Menu *mainMenu(Game *game) {
    Player *player = game->getPlayer();
    const auto menu = new Menu();
    menu->addContent(new label{
        "health: " + std::to_string(player->getHealth()) + "  energy: " + std::to_string(player->getEnergy())
    });
    if (player->getEnergy() <= 0) {
        menu->addContent(new label{
            "<bg_red>look for a room</bg_red>"
        });
    } else {
        menu->addContent(new button{
            "look for a room", [game] {
                game->setMenu(lookForRoom(game));
            }
        });
    }
    menu->addContent(new button{
        "restroom", [game, player] {
            player->setEnergy(player->getMaxEnergy());
            player->setHealth(player->getMaxHealth());
            const auto restroomMenu = new Menu();
            restroomMenu->addContent(new label{
                "energy and health restored"
            });
            restroomMenu->addContent(new button{
                "back", [game] {
                    game->setMenu(mainMenu(game));
                }
            });
            game->setMenu(restroomMenu);
        }
    });
    menu->addContent(new button{
        "inventory", [game] {
            game->getPlayer()->getInventory()->show(game);
        }
    });
    menu->addContent(new button{
        "exit", [game] {
            game->setMenu(nullptr);
            std::cout << "Closing the game..." << std::endl;
        }
    });
    return menu;
}

Menu *lookForRoom(Game *game) {
    Player *player = game->getPlayer();
    player->setEnergy(player->getEnergy() - 5);
    const auto menu = new Menu();
    const int randInt = rand() % 100;
    if (randInt < 45) {
        //45%
        menu->addContent(new label{
            "you found the treasure room"
        });
        menu->addContent(new button{
            "come in", [game] {
                const TreasureRoom *treasureRoom;
                if (rand() % 100 < 70) {
                    //70%
                    treasureRoom = new OrdinaryRoom();
                } else {
                    //30%
                    treasureRoom = new RareRoom();
                }
                treasureRoom->getChest(game)->show(game);
            }
        });
    } else if (randInt < 70) {
        //25%
        const int damage = rand() % 7 + 1;
        menu->addContent(new label{
            "you were attacked by a monster"
        });
        menu->addContent(new label{
            "damage received: <red>" + std::to_string(damage) + "</red>"
        });
        player->setHealth(player->getHealth() - damage);

        if (player->getHealth() <= 0) {
            menu->addContent(new button{
                "<red>game over</red>", [game] {
                    game->setMenu(nullptr);
                }
            });
            return menu;
        }
    } else {
        //30%
        menu->addContent(new label{
            "you didn't find anything"
        });
    }
    menu->addContent(new button{
        "back", [game] {
            game->setMenu(mainMenu(game));
        }
    });

    return menu;
}

Menu::~Menu() {
    for (int i = 0; i < this->elenents.size(); i++) {
        delete this->elenents[i];
    }
}
