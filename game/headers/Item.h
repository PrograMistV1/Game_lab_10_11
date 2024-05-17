#ifndef ITEM_H
#define ITEM_H

class Item {
    int count = 0;
public:
    Item();
    explicit Item(const Item *item);

    void setCount(int count);
    [[nodiscard]] int getCount() const;
};

#endif
