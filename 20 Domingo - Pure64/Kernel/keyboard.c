#include <keyboard.h>
#include <naiveConsole.h>
#include <lib.h>

#define BUFFER_SIZE 10

static char shift = 0;
static char buffer[BUFFER_SIZE] = {0};
static int buffer_index = 0;
static int isCharacter(int key);
static void pressBackspace();
static void moveCursorRight();
static void moveCursorLeft();
static void pressDel();

static unsigned char unshifted_keys[] = {
0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE,
TAB, 'q', 'w','e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER, 0,
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '~', '{', 0, 0, '}',
'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, '*', 0, ' ', CAPSLOCK,
F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, 0, 0,
INICIO, UP_PRESS, REPAG,'-', LEFT_PRESS, '5', RIGHT_PRESS, '+', FIN, DOWN_PRESS, AVPAG, INSERT, SUPR, 0, 0, '<', F11, F12};

static unsigned char shifted_keys[] = {
0, ESC, '!', '\"', '#', '$', '%', '&', '/', '(', ')', '=', '?', ' ', BACKSPACE,
9, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', ENTER, 0,
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\\', '[', ' ', 0, ']',
'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0, '*', 0, ' ', CAPSLOCK,
F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, 0, 0,
INICIO, UP_PRESS, REPAG, '-', LEFT_PRESS, 0, RIGHT_PRESS, '+', FIN, DOWN_PRESS, AVPAG, INSERT, SUPR, 0, 0, '>', F11, F12};

static void shiftBufferRight(int index)
{
	if(index == BUFFER_SIZE)
		return;
	shiftBufferRight(index+1);
	buffer[index] = buffer[index-1];
	return;
}

static void addtoBuffer(char character)
{
	if (buffer_index < BUFFER_SIZE)
	{
		shiftBufferRight(buffer_index);
		buffer[buffer_index] = character;
		buffer_index++;
	}
}

//Esta funcion deberia actualizar solo lo que describe el buffer. No borrar lo anterior.
void refreshScreen()
{
	clearScreen();
	print(buffer);
}



void keypress_handler()
{
	unsigned int key = readKey();
	if (key == LSHIFT_PRESS || key == RSHIFT_PRESS)
		shift = 1;
	else if(key == CAPSLOCK)
		shift = !shift;
	else if (key == LSHIFT_RELEASE || key == RSHIFT_RELEASE)
		shift = 0;
	else if (isCharacter(key))
		{
			switch(shift)
			{
				case 0:	addtoBuffer(unshifted_keys[key]);
								break;
				case 1:	addtoBuffer(shifted_keys[key]);
								break;
			}
			refreshScreen();
		}
		else
		{
			switch(key)
			{
				case BACKSPACE: 	pressBackspace();
													break;
				case LEFT_PRESS:	moveCursorLeft();
													break;
				case RIGHT_PRESS: moveCursorRight();
													break;
				case ENTER:				//SEND COMMAND;
													break;
				case TAB:					//WHATEVER TAB DOES;
													break;
				case SUPR:				pressDel();
													break;
			}
	}
	/* Debug Lines*/
	//print("   ");
	//printHex(key);
	//newLine();
}

static void pressBackspace()
{
	//Borra del buffer la ultima letra y la borra de pantalla
	buffer_index--;
	//Bring next elements back
	for (int i = buffer_index; i < BUFFER_SIZE; i++)
		buffer[i] = buffer[i+1];
	buffer[BUFFER_SIZE-1] = 0;
	refreshScreen();
}

static void pressDel()
{
	buffer_index++;
	pressBackspace();
}

static void moveCursorRight()
{
	if(buffer[buffer_index]!=0 && buffer_index < BUFFER_SIZE)
		buffer_index++;
}

static void moveCursorLeft()
{
	if (buffer_index > 0)
		buffer_index--;
}

//checks if key can be printed
static int isCharacter(int key)
{
	return ((key >= NUM_ROW_START && key <= NUM_ROW_END) || (key >= Q_ROW_START && key <= Q_ROW_END) || (key >= A_ROW_START && key <= A_ROW_END)
						|| (key >= Z_ROW_START && key <= Z_ROW_END)	|| (key == ASTERISK) ||(key == SPACEBAR) || (key == MINUS) || (key == PLUS)|| (key == GREATER));
}
