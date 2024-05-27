#include "headers/Item.h"

#include <iostream>

Item::Item(const Item *item) {
    this->count = item->count;
}

void Item::setCount(const int count) {
    this->count = count;
}

int Item::getCount() const {
    return this->count;
}

Menu *Item::pickUpMenu(Inventory *from, Inventory *to, const int index, Game *game) {
    auto menu = new Menu();
    menu->addContent(new label{
        "Do you really want to take " + this->getDisplayName() + "?"
    });

    menu->addContent(new button{
        "yes", [from, to, index, game, this] {
            bool found = false;
            int firstEmptySlot = -1;
            for (int i = 0; i < to->getSize(); i++) {
                Item *item = to->getItem(i);
                if (item == nullptr && firstEmptySlot == -1) {
                    firstEmptySlot = i;
                }
                if (item != nullptr && typeid(*item) == typeid(*this)) {
                    this->setCount(item->getCount() + this->getCount());
                    to->setItem(i, this);
                    from->setItem(index, nullptr);
                    found = true;
                    break;
                }
            }

            if (!found) {
                if (firstEmptySlot != -1) {
                    to->setItem(firstEmptySlot, this);
                    from->setItem(index, nullptr);
                    from->show(game);
                } else {
                    const auto noSpaceMenu = new Menu();
                    noSpaceMenu->addContent(new label{"There is no space in inventory."});
                    noSpaceMenu->addContent(new button{
                        "back", [from, game] {
                            from->show(game);
                        }
                    });
                    game->setMenu(noSpaceMenu);
                }
            } else {
                from->show(game);
            }
        }
    });
    menu->addContent(new button{
        "no", [from, game] {
            from->show(game);
        }
    });
    return menu;
}


void ItemFactory::registerDefaultItem(const Item *item) {
    this->defaultItems[item->getId()] = item->clone();
}

void ItemFactory::registerRareItem(const Item *item) {
    this->rareItems[item->getId()] = item->clone();
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

void Gold::use(Game *game, int slot, button *backButton) const {
    const auto menu = new Menu();
    menu->addContent(new label{"this item can't be used"});
    menu->addContent(backButton);
    game->setMenu(menu);
}

std::string Gold::getDisplayName() const {
    return "<yellow>gold</yellow> x" + std::to_string(this->getCount());
}

std::string Gold::getInfo() const {
    return "Precious coins (no use).";
}

Bread::Bread(const Bread *bread) {
    this->setCount(bread->getCount());
}

std::string Bread::getId() const {
    return "bread";
}

Item *Bread::clone() const {
    return new Bread(this);
}

void Bread::use(Game *game, int slot, button *backButton) const {
    Player *player = game->getPlayer();
    Inventory *inv = player->getInventory();
    Item *item = inv->getItem(slot);
    item->setCount(item->getCount() - 1);
    inv->setItem(slot, item);
    player->setEnergy(player->getEnergy() + 10);

    const auto menu = new Menu();
    menu->addContent(new label{"<green>10 energy restored</green>"});
    menu->addContent(backButton);
    game->setMenu(menu);
}

std::string Bread::getDisplayName() const {
    return "<yellow>bread</yellow> x" + std::to_string(this->getCount());
}

std::string Bread::getInfo() const {
    return "Food. Restores 10 energy.";
}

Rock::Rock(const Rock *rock) {
    this->setCount(rock->getCount());
}

std::string Rock::getId() const {
    return "rock";
}

Item *Rock::clone() const {
    return new Rock(this);
}

void Rock::use(Game *game, int slot, button *backButton) const {
    const auto menu = new Menu();
    menu->addContent(new label{"this item can't be used"});
    menu->addContent(backButton);
    game->setMenu(menu);
}

std::string Rock::getDisplayName() const {
    return "<blue>rock</blue> x" + std::to_string(this->getCount());
}

std::string Rock::getInfo() const {
    return "Ordinary garbage.";
}

HealthPotion::HealthPotion(const HealthPotion *healthPotion) {
    this->setCount(healthPotion->getCount());
}

std::string HealthPotion::getId() const {
    return "health_potion";
}

Item *HealthPotion::clone() const {
    return new HealthPotion(this);
}

void HealthPotion::use(Game *game, int slot, button *backButton) const {
    Player *player = game->getPlayer();
    Inventory *inv = player->getInventory();
    Item *item = inv->getItem(slot);
    item->setCount(item->getCount() - 1);
    inv->setItem(slot, item);
    player->setHealth(player->getHealth() + 10);

    const auto menu = new Menu();
    menu->addContent(new label{"<green>10 health restored</green>"});
    menu->addContent(backButton);
    game->setMenu(menu);
}

std::string HealthPotion::getDisplayName() const {
    return "<purple>health potion</purple> x" + std::to_string(this->getCount());
}

std::string HealthPotion::getInfo() const {
    return "Rare drop. Potion adding 10 health.";
}
