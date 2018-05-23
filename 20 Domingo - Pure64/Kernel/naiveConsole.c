#include <naiveConsole.h>
#include <stdint.h>
#include <lib.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void print(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		printChar(string[i]);
}

void printChar(char character)
{
	*currentVideo = character;
	currentVideo += 2;
}

void printFormat(const char * string, enum COLOR background_color, enum COLOR text_color)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		printCharFormat(string[i], background_color, text_color);
}

void printCharFormat(char character, enum COLOR background_color, enum COLOR text_color)
{
	*currentVideo = character;
	currentVideo += 1;
	*currentVideo = background_color*16 + text_color;
	currentVideo += 1;
}

void newLine()
{
	do
	{
		printChar(' ');
	}while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void printDec(uint64_t value)
{
	printBase(value, 10);
}

void printHex(uint64_t value)
{
	printBase(value, 16);
}

void printBin(uint64_t value)
{
	printBase(value, 2);
}

void printBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    print(buffer);
}

void clearScreen()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

static char translateTime(char value)
{
	return (value/16)*10 + (value%16);
}

static void translateAndPrintTime(char value)
{
	char time = translateTime(value);
	if (time<10)
		printChar('0');
	printDec(time);
}

void printCurrentTime()
{
	translateAndPrintTime(getHours());
	printChar(':');
	translateAndPrintTime(getMinutes());
	printChar(':');
	translateAndPrintTime(getSeconds());
	newLine();
}
