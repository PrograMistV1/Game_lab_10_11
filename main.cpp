#include <iostream>

#include "game/headers/Game.h"

int main() {
    srand(time(nullptr));
    (new Game())->init();
    return 0;
}
