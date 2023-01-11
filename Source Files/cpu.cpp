#include <QApplication>
#include <iostream>
#include <fstream>
#include <ctime>

#include "cpu.h"
#include "mainwindow.h"

long Cpu::romFileSize = 0;
Cpu::STATE Cpu::state = STATE::PAUSED;

Cpu::Cpu()
{
	srand(time(0));

	// Init I Register
	I = 0;

	// Init the SP 
	SP = 0;

	// Init PC at 0x200 because Chip8 program usually start at 0x200
	PC = 0x200;

	// Init all registers to 0 and all keys to false
	for (int i = 0; i < 16; i++)
		Registers[i] = 0;

	// Filling memory with 0
	for (int i = 0; i < 0x1000; i++)
		RAM[i] = 0;

	// Load all fonts to memory
	uint8_t fonts[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0,
		0x20, 0x60, 0x20, 0x20, 0x70,
		0xF0, 0x10, 0xF0, 0x80, 0xF0,
		0xF0, 0x10, 0xF0, 0x10, 0xF0,
		0x90, 0x90, 0xF0, 0x10, 0x10,
		0xF0, 0x80, 0xF0, 0x10, 0xF0,
		0xF0, 0x80, 0xF0, 0x90, 0xF0,
		0xF0, 0x10, 0x20, 0x40, 0x40,
		0xF0, 0x90, 0xF0, 0x90, 0xF0,
		0xF0, 0x90, 0xF0, 0x10, 0xF0,
		0xF0, 0x90, 0xF0, 0x90, 0x90,
		0xE0, 0x90, 0xE0, 0x90, 0xE0,
		0xF0, 0x80, 0x80, 0x80, 0xF0,
		0xE0, 0x90, 0x90, 0x90, 0xE0,
		0xF0, 0x80, 0xF0, 0x80, 0xF0,
		0xF0, 0x80, 0xF0, 0x80, 0x80
	};

	for (int i = 0; i < 0x200; i++)
		RAM[i] = fonts[i];

	// Init screen buffer with 0
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 32; j++)
		{
			screenBuffer[i][j] = 0x0;
		}

	// Init timers
	DT = 0;
	ST = 0;

	// Setting current opcode to the first word in memory
	currOpcode = RAM[PC];
}

Cpu::~Cpu()
{

}

uint16_t Cpu::getPC()
{
	return PC;
}

uint16_t Cpu::getSP()
{
	return SP;
}

uint16_t Cpu::getI()
{
	return I;
}

uint16_t Cpu::getDT()
{
	return DT;
}

uint16_t Cpu::getST()
{
	return ST;
}

std::uint8_t* Cpu::getRegisters()
{
	return Registers;
}

std::map<uint16_t, std::string> Cpu::getMnemonics()
{
	return disassembler->mnemonicsMap;
}

void Cpu::loadRom(std::string filePath)
{
	// Opening file
	std::ifstream Rom(filePath, std::ios::binary | std::ios::ate);

	// If file is open 
	if (Rom.is_open())
	{
		// Getting file size
		romFileSize = Rom.tellg();

		// Creating buffer of the size of the rom
		char* buff = new char[romFileSize];

		// Reading rom to buffer
		Rom.seekg(0, std::ios::beg);
		Rom.read(buff, romFileSize);

		// Closing file
		Rom.close();

		// Mnemonics
		std::vector<uint8_t> tmpBuff(buff, buff + romFileSize);
		disassembler = new Chip8Disassembler(tmpBuff);
		disassembler->disassemble();

		// Loading Rom to memory
		for (int i = 0; i <= romFileSize; i++)
			RAM[i + 0x200] = buff[i];
		delete[] buff;

		// Setting CPU State
		state = STATE::RUNNING;
	}

	// If file not found
	else
	{
		std::cout << "Rom file " << filePath << " not found. Exiting..." << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Cpu::reset()
{
	// Init I Register
	I = 0;

	// Init the SP 
	SP = 0;

	// Init PC at 0x200 because Chip8 program usually start at 0x200
	PC = 0x200;

	// Init all registers to 0 and all keys to false
	for (int i = 0; i < 16; i++)
		Registers[i] = 0;

	// Filling memory with 0
	for (int i = 0; i < 0x200; i++)
		RAM[i] = 0;

	// Load all fonts to memory
	uint8_t fonts[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0,
		0x20, 0x60, 0x20, 0x20, 0x70,
		0xF0, 0x10, 0xF0, 0x80, 0xF0,
		0xF0, 0x10, 0xF0, 0x10, 0xF0,
		0x90, 0x90, 0xF0, 0x10, 0x10,
		0xF0, 0x80, 0xF0, 0x10, 0xF0,
		0xF0, 0x80, 0xF0, 0x90, 0xF0,
		0xF0, 0x10, 0x20, 0x40, 0x40,
		0xF0, 0x90, 0xF0, 0x90, 0xF0,
		0xF0, 0x90, 0xF0, 0x10, 0xF0,
		0xF0, 0x90, 0xF0, 0x90, 0x90,
		0xE0, 0x90, 0xE0, 0x90, 0xE0,
		0xF0, 0x80, 0x80, 0x80, 0xF0,
		0xE0, 0x90, 0x90, 0x90, 0xE0,
		0xF0, 0x80, 0xF0, 0x80, 0xF0,
		0xF0, 0x80, 0xF0, 0x80, 0x80
	};

	for (int i = 0; i < 0x200; i++)
		RAM[i] = fonts[i];

	// Init screen buffer with 0
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 32; j++)
		{
			screenBuffer[i][j] = 0x0;
		}

	// Init timers
	DT = 0;
	ST = 0;

	// Setting current opcode to the first word in memory
	currOpcode = RAM[PC];
}

void Cpu::updateTimers()
{
	// Decreasing main timer
	if (DT > 0)
		DT--;

	// Decrease sound timer
	if (ST > 0)
		ST--;
}

void Cpu::run()
{
	// For the loop
	bool running = true;

	// While running
	while (running)
	{
		QApplication::instance()->processEvents();
		// Do a CPU step
		step();
	}
}

void Cpu::step()
{
	// Fetch
	fetch();

	// Decode and excute
	decodeAndExecute();

	// Updating timers
	updateTimers();
}

void Cpu::fetch()
{
	// Getting the Word pointed at PC in memory
	currOpcode = (RAM[PC] << 8) | RAM[PC + 1];
	PC += 2;
}

void Cpu::decodeAndExecute()
{
	switch (currOpcode & 0xF000)
	{
		// The 0x0FFF opcodes
	case 0x0000:
		switch (currOpcode & 0x000F)
		{
		case 0x0000: CLS(); break;
		case 0x000E: RET(); break;
		default: break;
		}
		break;

		// The 0x1FFF opcode
	case 0x1000: JMP(); break;

		// The 0x2FFF opcode
	case 0x2000: CALL(); break;

		// The 0x3FFF opcode
	case 0x3000: SE_Vx(); break;

		// The 0x4FFF opcode
	case 0x4000: SNE_Vx(); break;

		// The 0x5FFF opcode
	case 0x5000: SE_Vx_Vy(); break;

		// The 0x6FFF opcode
	case 0x6000: LD_Vx(); break;

		// The 0x7FFF opcode
	case 0x7000: ADD_Vx(); break;

		// The 0x7FFF opcodes
	case 0x8000:
	{
		// indexes
		int x = (currOpcode & 0x0F00) >> 8;
		int y = (currOpcode & 0x00F0) >> 4;

		switch (currOpcode & 0x000F)
		{
		case 0x0000: LD_Vx_Vy(x, y); break;
		case 0x0001: OR_Vx_Vy(x, y); break;
		case 0x0002: AND_Vx_Vy(x, y); break;
		case 0x0003: XOR_Vx_Vy(x, y); break;
		case 0x0004: ADD_Vx_Vy(x, y); break;
		case 0x0005: SUB_Vx_Vy(x, y); break;
		case 0x0006: SHR_Vx(x); break;
		case 0x0007: SUBN_Vx_Vy(x, y); break;
		case 0x000E: SHL_Vx(x); break;
		default: break;
		}
		break;
	}

	// The 0x9FFF opcodes
	case 0x9000: SNE_Vx_Vy();  break;

	// The 0xAFFF opcodes
	case 0xA000: LD_I(); break;

	// The 0xBFFF opcodes
	case 0xB000: JP_V0(); break;

	// The 0xCFFF opcodes
	case 0xC000: RND_Vx(); break;

	// The 0xDFFF opcodes
	case 0xD000: DRW_Vx_Vy(); break;

	// The 0xEFFF opcodes
	case 0xE000:
	{
		switch (currOpcode & 0x00F0)
		{
		case 0x0090: SKP_Vx(); break;
		case 0x00A0: SKNP_Vx(); break;
		default: break;
		}
	}
	break;

	// The 0xFFFF opcodes
	case 0xF000:
	{
		switch (currOpcode & 0x00F0)
		{
		case 0x0000:
		{
			switch (currOpcode & 0x000F)
			{
			case 0x0007: LD_Vx_DT(); break;
			case 0x000A: LD_Vx_k(); break;
			default: break;
			}
		}
		case 0x0010:
		{
			switch (currOpcode & 0x000F)
			{
			case 0x0005: LD_DT_Vx(); break;
			case 0x0008: LD_ST_Vx(); break;
			case 0x000E: ADD_I_Vx(); break;
			default: break;
			}
		}
		case 0x0020: LD_F_Vx(); break;
		case 0x0030: LD_B_Vx(); break;
		case 0x0050: LD__I__Vx(); break;
		case 0x0060: LD__Vx__I(); break;
		default: break;
		}
	}
	break;
	default:
		exit(EXIT_FAILURE);

	}
}

void Cpu::setKeys(std::bitset<16> value)
{
	keys = value;
}

std::bitset<16> Cpu::getKeys()
{
	return keys;
}

void Cpu::CLS()
{
	// Zeroing all values in the buffer
	MainWindow::img.fill(QColor(0,0,0));
}

void Cpu::RET()
{
	// Setting PC to the last value inserted in Stack
	if (Stack.size() > 0)
		PC = Stack[Stack.size() - 1];
	else PC = Stack[0];
	// Decreasing SP
	SP--;
}

void Cpu::JMP()
{
	// Setting PC to nnn
	PC = currOpcode & 0x0FFF;
}

void Cpu::CALL()
{
	Stack.emplace_back(PC);
	SP++;
	PC = currOpcode & 0x0FFF;
}

void Cpu::SE_Vx()
{
	int index = (currOpcode & 0x0F00) >> 8;
	if (Registers[index] == (currOpcode & 0x00FF))
		PC += 2;
}

void Cpu::SNE_Vx()
{
	int index = (currOpcode & 0x0F00) >> 8;
	if (Registers[index] != (currOpcode & 0x00FF))
		PC += 2;
}

void Cpu::SE_Vx_Vy()
{
	int x = (currOpcode & 0x0F00) >> 8;
	int y = (currOpcode & 0x00F0) >> 4;
	if (Registers[x] == Registers[y])
		PC += 2;
}

void Cpu::LD_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	Registers[x] = currOpcode & 0x00FF;
}

void Cpu::ADD_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	Registers[x] += (uint8_t)(currOpcode & 0x00FF);
}

void Cpu::LD_Vx_Vy(int x, int y)
{
	Registers[x] = Registers[y];
}

void Cpu::OR_Vx_Vy(int x, int y)
{
	Registers[x] |= Registers[y];
}

void Cpu::AND_Vx_Vy(int x, int y)
{
	Registers[x] &= Registers[y];
}

void Cpu::XOR_Vx_Vy(int x, int y)
{
	Registers[x] ^= Registers[y];
}

void Cpu::ADD_Vx_Vy(int x, int y)
{
	uint16_t val = Registers[x] + Registers[y];
	if (val >= 0x100)
		Registers[15] = 1;
	else Registers[15] = 0;

	Registers[x] = val & 0xFF;
}

void Cpu::SUB_Vx_Vy(int x, int y)
{
	if (Registers[x] > Registers[y])
		Registers[15] = 1;
	else Registers[15] = 0;

	Registers[x] -= Registers[y];
}

void Cpu::SUBN_Vx_Vy(int x, int y)
{
	if (Registers[x] < Registers[y])
		Registers[15] = 1;
	else Registers[15] = 0;

	Registers[x] = Registers[y] - Registers[x];
}

void Cpu::SHR_Vx(int x)
{
	if (Registers[x] & 0b00000001 == 1)
		Registers[15] = 1;
	else Registers[15] = 0;

	Registers[x] = Registers[x] >> 1;
}

void Cpu::SHL_Vx(int x)
{
	if (Registers[x] & 0b10000000 == 0b10000000)
		Registers[15] = 1;
	else Registers[15] = 0;

	Registers[x] = Registers[x] << 1;
}

void Cpu::SNE_Vx_Vy()
{
	int x = (currOpcode & 0x0F00) >> 8;
	int y = (currOpcode & 0x00F0) >> 4;
	if (Registers[x] != Registers[y])
		PC += 2;
}

void Cpu::LD_I()
{
	I = currOpcode & 0x0FFF;
}

void Cpu::JP_V0()
{
	PC = (currOpcode & 0x0FFF) + Registers[0];
}

void Cpu::RND_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	Registers[x] = (rand() % 0xFF) & (currOpcode & 0x00FF);
}

void Cpu::DRW_Vx_Vy()
{
	uint8_t x = Registers[(currOpcode & 0x0F00) >> 8];
	uint8_t y = Registers[(currOpcode & 0x00F0) >> 4];
	uint8_t n = currOpcode & 0x000F;
	uint8_t pixel;

	Registers[15] = 0;

	for (int i = 0; i < n; i++)
	{
		pixel = RAM[I + i];
		for (int j = 0; j < 8; j++)
		{
			if ((pixel & (0x80 >> j)) != 0)
			{
				if (MainWindow::img.pixelColor(x + j, y + i) == QColor(255, 255, 255))
				{
					Registers[15] = 1;
					MainWindow::img.setPixelColor(x  + j, y + i, QColor(0,0,0));
				}
				else MainWindow::img.setPixelColor(x + j, y + i, QColor(255, 255, 255));
			}
		}
	}

}

void Cpu::SKP_Vx()
{
	uint8_t x = (currOpcode & 0x0F00) >> 8;
	if (keys[Registers[x]] == 1)
	{
		keys[Registers[x]] = 0;
		PC += 2;
	}
}

void Cpu::SKNP_Vx()
{
	uint8_t x = (currOpcode & 0x0F00) >> 8;
	keys = std::bitset<16>().set();
	if (keys[Registers[x]] == 1)
	{
		keys[Registers[x]] = 0;
		PC += 2;
	}
}

void Cpu::LD_Vx_DT()
{
	int x = (currOpcode & 0x0F00) >> 8;
	Registers[x] = DT;
}

void Cpu::LD_Vx_k()
{
	// TODO
}

void Cpu::LD_DT_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	DT = Registers[x];
}

void Cpu::LD_ST_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	ST = Registers[x];
}

void Cpu::ADD_I_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	I += Registers[x];
}

void Cpu::LD_F_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	I = Registers[x] * 5;
}

void Cpu::LD_B_Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	RAM[I] = Registers[x] / 100;
	RAM[I + 1] = (Registers[x] / 10) % 10;
	RAM[I + 2] = Registers[x] % 10;
}

void Cpu::LD__I__Vx()
{
	int x = (currOpcode & 0x0F00) >> 8;
	for (int i = 0; i <= x; i++)
		RAM[I + i] = Registers[i];
	I += x + 1; // TOCHECK
}

void Cpu::LD__Vx__I()
{
	int x = (currOpcode & 0x0F00) >> 8;
	for (int i = 0; i <= x; i++)
		Registers[i] = RAM[I + i];
	I += x + 1; // TOCHECK
}