#include "headers/Inventory.h"

Inventory::Inventory(const int size, const std::string &title) : size(size) , title(title){
}

void Inventory::setSize(const int size) {
    this->size = size;
}

int Inventory::getSize() const {
    return this->size;
}

void Inventory::setItem(const int index, const Item *item) {
    if (index >= 0 && index < this->size) {
        if (this->getItem(index) != nullptr) {
            delete this->items[index];
            this->items.erase(index);
        }
        if (item != nullptr && item->getCount() > 0) {
            this->items[index] = item->clone();
        }
    }
}

Item *Inventory::getItem(const int index) const {
    const auto it = this->items.find(index);
    if (it != this->items.end()) {
        return it->second->clone();
    }
    return nullptr;
}

void Inventory::show(Game *game) {
    const auto backButton = new button{
        "back", [game] {
            game->setMenu(mainMenu(game));
        }
    };
    this->show(game, backButton);
}


void Inventory::show(Game *game, button *backButton) {
    const auto menu = new Menu();
    menu->addContent(new label{this->getTitle()});
    menu->addContent(backButton);

    for (int index = 0; index < this->getSize(); index++) {
        Item *item = this->getItem(index);
        if (item != nullptr) {
            menu->addContent(new button{
                std::to_string(index + 1) + ": " + item->getDisplayName(), [game, index, this, backButton] {
                    this->showItemMenu(game, index, backButton->clone());
                }
            });
        } else {
            menu->addContent(new button{
                std::to_string(index + 1) + ": ", [] {
                }
            });
        }
    }
    game->setMenu(menu);
}

std::string Inventory::getTitle() const {
    return this->title;
}

void Inventory::showItemMenu(Game *game, const int index, button *backButton) {
    const auto menu = new Menu();
    Item *item = this->getItem(index);
    menu->addContent(new label{item->getInfo()});
    menu->addContent(new button{
        "use", [game, index, item, this, backButton] {
            item->use(game, index, new button{
                          "back", [this, game, backButton] {
                              this->show(game, backButton);
                          }
                      });
        }
    });
    menu->addContent(new button{
        "replace", [game, this, backButton, index] {
            const auto replaceMenu = new Menu();
            replaceMenu->addContent(new button{
                "cancel", [game, this, backButton] {
                    this->show(game, backButton);
                }
            });
            for (int indexTo = 0; indexTo < this->getSize(); indexTo++) {
                const Item *item = this->getItem(indexTo);

                const std::function replaceFunc = [this, indexTo, index, game, backButton] {
                    const Item *itemFrom = this->getItem(indexTo);
                    const Item *itemTo = this->getItem(index);
                    this->setItem(indexTo, itemTo);
                    this->setItem(index, itemFrom);
                    this->show(game, backButton);
                };

                if (item != nullptr) {
                    if (index == indexTo) {
                        replaceMenu->addContent(new label{
                            "<bg_red>" + std::to_string(indexTo + 1) + ": " + item->getDisplayName() + "</bg_red>"
                        });
                    } else {
                        replaceMenu->addContent(new button{
                            std::to_string(indexTo + 1) + ": " + item->getDisplayName(), replaceFunc
                        });
                    }
                } else {
                    replaceMenu->addContent(new button{
                        std::to_string(indexTo + 1) + ": ", replaceFunc
                    });
                }
            }
            game->setMenu(replaceMenu);
        }
    });
    menu->addContent(new button{
        "throw away", [this, game, backButton, index] {
            this->setItem(index, nullptr);
            this->show(game, backButton);
        }
    });
    menu->addContent(new button{
        "back", [this, game, backButton] {
            this->show(game, backButton);
        }
    });
    game->setMenu(menu);
}
