#include <string>

#include "game/Console.h"

[[noreturn]] int main() {
    constexpr std::string_view formattedString = "<red>привет, <blue>мир</blue>! <default>как</default> дела?</red>";
    printFormattedString(formattedString);
}
