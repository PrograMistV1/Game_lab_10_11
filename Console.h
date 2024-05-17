#pragma once

#include <iostream>
#include <map>

#ifdef _WIN32

#include <windows.h>

using Color = WORD;
#else
using Color = std::string_view;
#endif

/**
 * Windows uses its own API to set text color
 * https://learn.microsoft.com/en-us/windows/console/console-screen-buffers
 *
 * UNIX systems use ANSI.
 * Code values can be found in https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
 */
inline std::map<std::string_view, Color> formatMap = {
#ifdef _WIN32
        {"default", 0x1111}, //this is necessary to indicate color cleaning
        {"black", 0}, //black is the absence of color
        {"red", FOREGROUND_RED},
        {"green", FOREGROUND_GREEN},
        {"blue", FOREGROUND_BLUE},
        {"yellow", FOREGROUND_RED | FOREGROUND_GREEN},
        {"purple", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY},
        {"cyan", FOREGROUND_GREEN | FOREGROUND_BLUE},
        {"grey", FOREGROUND_INTENSITY},
        {"bg_red", BACKGROUND_RED},
        {"bg_green", BACKGROUND_GREEN},
        {"bg_yellow", BACKGROUND_RED | BACKGROUND_GREEN},
        {"bg_blue", BACKGROUND_BLUE},
        {"bg_purple", BACKGROUND_RED | BACKGROUND_BLUE},
        {"bg_cyan", BACKGROUND_GREEN | BACKGROUND_BLUE},
        {"bg_grey", BACKGROUND_INTENSITY}
#else
        {"default", "0"},
        {"black", "30"},
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

/**
 * Checks if a specified color exists
 */
bool issetColor(const std::string_view &tag);

void setConsoleTextColor(const Color &color);

/**
 * Formats the passed string and outputs it to the console
 */
void printFormattedString(const std::string_view &input);

/**
 * Clears console
 */
void clearConsole();
