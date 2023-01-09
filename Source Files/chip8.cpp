#include "chip8.h"
#include <QApplication>

Chip8::Chip8()
{
	cpu = new Cpu();
	romFile = "maze.ch8";
	cpu->loadRom(romFile);
}

Chip8::~Chip8()
{

}

void Chip8::emulate()
{
	while (true)
	{
		QApplication::instance()->processEvents();
		cpu->step();
	}
}

Cpu* Chip8::getCpu()
{
	return cpu;
}