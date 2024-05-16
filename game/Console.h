#pragma once

#include <iostream>
#include <map>

#ifdef _WIN32
#include <windows.h>
using Color = WORD;
#else
using Color = std::string_view;
#endif

inline std::map<std::string_view, Color> formatMap = {
#ifdef _WIN32
    {"default", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE},
    {"red", FOREGROUND_RED | FOREGROUND_INTENSITY},
    {"green", FOREGROUND_GREEN | FOREGROUND_INTENSITY},
    {"blue", FOREGROUND_BLUE | FOREGROUND_INTENSITY},
    {"yellow", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY}
#else
    {"default", "0"},
    {"red", "31"},
    {"green", "32"},
    {"yellow", "33"},
    {"blue", "34"},
    {"purple", "35"},
    {"cyan", "36"},
    {"grey", "37"},
    {"bg_red", "41"},
    {"bg_green", "42"},
    {"bg_yellow", "43"},
    {"bg_blue", "44"},
    {"bg_purple", "45"},
    {"bg_cyan", "46"},
    {"bg_grey", "47"}
#endif
};

bool issetColor(const std::string_view &tag);

void setConsoleTextColor(const Color &color);

void printFormattedString(const std::string_view &input);

void clearConsole();
