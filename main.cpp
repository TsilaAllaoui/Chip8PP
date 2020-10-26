#include "chip8.h"
#include <SDL/SDL.h>

int main(int argc, char **argv)
{
	Chip8().emulate();
}
