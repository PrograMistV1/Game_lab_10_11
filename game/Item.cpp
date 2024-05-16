#include "Item.h"

Item::Item() = default;

Item::Item(const Item *item) {
    this->count = item->count;
}

void Item::setCount(const int count) {
    this->count = count;
}

int Item::getCount() const {
    return this->count;
}
