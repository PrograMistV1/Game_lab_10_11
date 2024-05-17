#include "./Console.h"

#include <cstdlib>
#include <stack>
#include <string>

bool issetColor(const std::string_view &tag) {
    const auto it = formatMap.find(tag);
    return it != formatMap.end();
}

void setConsoleTextColor(const Color &color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    Color oldColor;
    if (color == 0x1111) { //0x1111 means completely clear formatting
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return;
    }
    //Checking which plan (foreground or background) the user is trying to change, and then resetting the old one
    if(color & FOREGROUND_RED || color & FOREGROUND_GREEN || color & FOREGROUND_BLUE || color == 0){
        oldColor = bufferInfo.wAttributes & ~(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        oldColor = bufferInfo.wAttributes & ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    }
    //Setting a new color
    SetConsoleTextAttribute(hConsole, oldColor | color);
#else
    //ESC symbol
    std::cout << "\033[" << color << "m";
#endif
}

void printFormattedString(const std::string_view &input) {
    std::stack<std::string_view> colorStack;
    size_t pos = 0;

    while (pos < input.length()) {
        if (input[pos] == '<') {
            const size_t endPos = input.find('>', pos);
            if (endPos != std::string_view::npos) {
                std::string_view tag = input.substr(pos + 1, endPos - pos - 1);
                if (tag[0] == '/') {
                    tag = tag.substr(1); //getting rid of '/'
                    if (!colorStack.empty()) {
                        //check the nesting of tags
                        if (colorStack.top() == tag) {
                            colorStack.pop();
                            if (!colorStack.empty()) {
                                setConsoleTextColor(formatMap[colorStack.top()]);
                            } else {
                                setConsoleTextColor(formatMap["default"]);
                            }
                        } else {
                            std::cout << "</" << tag << '>';
                        }
                    }
                } else {
                    if (issetColor(tag)) {
                        colorStack.push(tag);
                        setConsoleTextColor(formatMap[tag]);
                    } else {
                        std::cout << "<" << tag << '>';
                    }
                }
                pos = endPos + 1;
            }
        } else {
            std::cout << input[pos];
            pos++;
        }
    }
    std::cout << std::endl;
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
