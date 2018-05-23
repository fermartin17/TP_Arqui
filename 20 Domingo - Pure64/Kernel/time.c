#include <time.h>
#include <naiveConsole.h>
#include <keyboard.h>

static unsigned long ticks = 0;
static unsigned long next_time = 1;

void timer_handler() {
	ticks++;
	if(seconds_elapsed() == next_time)
	{
		
		refreshScreen();
		next_time += 1;
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
