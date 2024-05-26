#include "headers/Item.h"

Item::Item(const Item *item) {
    this->count = item->count;
}

void Item::setCount(const int count) {
    this->count = count;
}

int Item::getCount() const {
    return this->count;
}

Menu *Item::pickUpMenu(Inventory *inventory, const int index, Game *game) {
    auto menu = new Menu();
    const Item *item = inventory->getItem(index);
    menu->addContent(new label{
        std::string("Do you really want to take ") + std::to_string(item->getCount()) + " " + item->getDisplayName() +
        "?"
    });
    menu->addContent(new button{
        "yes", [inventory, index, game] {
            inventory->setItem(index, nullptr);
            inventory->show(game);
        }
    });
    menu->addContent(new button{
        "no", [inventory, game] {
            inventory->show(game);
        }
    });
    return menu;
}


void ItemFactory::registerDefaultItem(const Item *item) {
    this->defaultItems[item->getId()] = item->clone();
}

std::map<std::string, Item *> ItemFactory::getDefaultItems() {
    return this->defaultItems;
}

std::map<std::string, Item *> ItemFactory::getRareItems() {
    return this->rareItems;
}

Gold::Gold(const Gold *gold) {
    this->setCount(gold->getCount());
}

std::string Gold::getId() const {
    return "gold";
}

Item *Gold::clone() const {
    return new Gold(this);
}

void Gold::use(Player *player) const {
}

std::string Gold::getDisplayName() const {
    return "<yellow>gold</yellow> x" + std::to_string(this->getCount());
}
