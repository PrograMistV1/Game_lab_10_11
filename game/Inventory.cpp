#include "headers/Inventory.h"

Inventory::Inventory(const int size) : size(size){
}

void Inventory::setSize(const int size) {
    this->size = size;
}

int Inventory::getSize() const {
    return this->size;
}

void Inventory::setItem(const int index, const Item *item) {
    if (index >= 0 && index < this->size) {
        if (items.contains(index)) {
            delete items[index];
        }
    }
    items[index] = new Item(*item);
}

Item* Inventory::getItem(const int index) const {
    const auto it = this->items.find(index);
    if (it != this->items.end()) {
        return it->second;
    }
    return nullptr;
}

