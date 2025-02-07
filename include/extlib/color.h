#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>

std::string reset();
std::string bold();
std::string faint();
std::string italic();
std::string underline();
std::string inverse();
std::string strikethrough();

std::string fgBlack();
std::string fgRed();
std::string fgGreen();
std::string fgYellow();
std::string fgBlue();
std::string fgMagenta();
std::string fgCyan();
std::string fgWhite();

std::string bgBlack();
std::string bgRed();
std::string bgGreen();
std::string bgYellow();
std::string bgBlue();
std::string bgMagenta();
std::string bgCyan();
std::string bgWhite();

std::string fgBrightBlack();
std::string fgBrightRed();
std::string fgBrightGreen();
std::string fgBrightYellow();
std::string fgBrightBlue();
std::string fgBrightMagenta();
std::string fgBrightCyan();
std::string fgBrightWhite();

std::string bgBrightBlack();
std::string bgBrightRed();
std::string bgBrightGreen();
std::string bgBrightYellow();
std::string bgBrightBlue();
std::string bgBrightMagenta();
std::string bgBrightCyan();
std::string bgBrightWhite();

#endif // COLOR_H