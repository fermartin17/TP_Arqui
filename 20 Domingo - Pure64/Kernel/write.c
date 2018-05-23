#include <naiveConsole.h>

enum FD{ STDOUT=0, STDERR};

void write_handler(uint64_t fd, char * buffer, int strlen)
{
	char cadena[strlen+1];
	int i=0;
	for (i = 0; i < strlen; ++i)
		cadena[i] = buffer[i];
	cadena[i]= 0;
	switch(fd)
	{
		case STDOUT:	print(cadena);
									break;
		case STDERR:  printFormat(cadena, BLACK, RED);
									break;
	}
}
