#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

enum COLOR
{
  	BLACK=0, BLUE, GREEN, TEAL, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, INDIGO, LIME, CYAN, SALMON, PINK, YELLOW, WHITE
};

void print(const char * string);
void printFormat(const char * string, enum COLOR background_color, enum COLOR text_color);
void printChar(char character);
void printCharFormat(char character, enum COLOR background_color, enum COLOR text_color);
void newLine();
void printDec(uint64_t value);
void printHex(uint64_t value);
void printBin(uint64_t value);
void printBase(uint64_t value, uint32_t base);
void clearScreen();
void printCurrentTime();

#endif
