#include "disassembler.h"

#include <algorithm>
#include <iostream>
#include <sstream>

Chip8Disassembler::Chip8Disassembler(const std::vector<uint8_t> &_rom)
{
	// If the byte array given is empty
	if (_rom.size() == 0)
	{
		std::cout << "Rom is empty..." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	rom = _rom;
}

Chip8Disassembler::~Chip8Disassembler()
{

}

void Chip8Disassembler::disassemble()
{
	auto stohex = [](uint16_t val, std::string prefix = "#") -> std::string
	{
		std::stringstream ss;
		std::string s = prefix + ((std::to_string(val).size() == 1) ? "0" : "");
		ss << std::hex << val;
		std::string _s = ss.str();
		std::transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
		return s + _s;
	};


	for (long i = 0; i < rom.size(); i+=2)
	{
		uint16_t currOpcode = (rom[i] << 8);
		if (i != rom.size() - 1)
			 currOpcode |= rom[i + 1];

		switch (currOpcode & 0xF000)
		{
			// The 0x0FFF opcodes
		case 0x0000:
			switch (currOpcode & 0x000F)
			{
			case 0x0000: mnemonics.emplace_back("CLS"); break;
			case 0x000E: mnemonics.emplace_back("RET"); break;
			default: break;
			}
			break;

			// The 0x1FFF opcode
		case 0x1000:  mnemonics.emplace_back("JP " + stohex(currOpcode & 0x0FFF)); break;

			// The 0x2FFF opcode
		case 0x2000: mnemonics.emplace_back("CALL " + stohex(currOpcode & 0x0FFF)); break;

			// The 0x3FFF opcode
		case 0x3000: mnemonics.emplace_back("SE  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", ") + stohex(currOpcode & 0x00FF)); break;

			// The 0x4FFF opcode
		case 0x4000: mnemonics.emplace_back("SNE  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", ") + stohex(currOpcode & 0x00FF)); break;

			// The 0x5FFF opcode
		case 0x5000: mnemonics.emplace_back("SE  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;

			// The 0x6FFF opcode
		case 0x6000: mnemonics.emplace_back("LD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", ") + stohex(currOpcode & 0x00FF)); break;

			// The 0x7FFF opcode
		case 0x7000: mnemonics.emplace_back("ADD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", ") + stohex(currOpcode & 0x00FF)); break;; break;

			// The 0x7FFF opcodes
		case 0x8000:
		{
			// indexes
			int x = (currOpcode & 0x0F00) >> 8;
			int y = (currOpcode & 0x00F0) >> 4;

			switch (currOpcode & 0x000F)
			{
			case 0x0000: mnemonics.emplace_back("LD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0001: mnemonics.emplace_back("OR  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0002: mnemonics.emplace_back("AND  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0003: mnemonics.emplace_back("XOR  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0004: mnemonics.emplace_back("ADD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0005: mnemonics.emplace_back("SUB  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0006: mnemonics.emplace_back("SHR  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x0007: mnemonics.emplace_back("SUBN  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;
			case 0x000E: mnemonics.emplace_back("SHL  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", {, V") + std::to_string((currOpcode & 0x00F0) >> 4) + "}"); break;
			default: break;
			}
			break;
		}

		// The 0x9FFF opcodes
		case 0x9000: mnemonics.emplace_back("SNE  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4));  break;

			// The 0xAFFF opcodes
		case 0xA000: mnemonics.emplace_back("LD  I , " + stohex(currOpcode & 0x0FFF)); break;

			// The 0xBFFF opcodes
		case 0xB000: mnemonics.emplace_back("JP  V0 , " + stohex(currOpcode & 0x0FFF)); break;

			// The 0xCFFF opcodes
		case 0xC000: mnemonics.emplace_back("RND  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", ") + stohex(currOpcode & 0x00FF)); break;

			// The 0xDFFF opcodes
		case 0xD000: mnemonics.emplace_back("DRW  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", V") + std::to_string((currOpcode & 0x00F0) >> 4)); break;

			// The 0xEFFF opcodes
		case 0xE000:
		{
			switch (currOpcode & 0x00F0)
			{
			case 0x0090: mnemonics.emplace_back("SKP  V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
			case 0x00A0: mnemonics.emplace_back("SKNP  V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
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
				case 0x0007: mnemonics.emplace_back("LD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", DT")); break;
				case 0x000A: mnemonics.emplace_back("LD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", K")); break;
				default: break;
				}
			}
			case 0x0010:
			{
				switch (currOpcode & 0x000F)
				{
				case 0x0005: mnemonics.emplace_back("LD  DT, V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
				case 0x0008: mnemonics.emplace_back("LD  ST, V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
				case 0x000E: mnemonics.emplace_back("ADD  I, V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
				default: break;
				}
			}
			case 0x0020: mnemonics.emplace_back("LD  F, V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
			case 0x0030: mnemonics.emplace_back("LD  B, V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
			case 0x0050: mnemonics.emplace_back("LD  [I], V" + std::to_string((currOpcode & 0x0F00) >> 8)); break;
			case 0x0060: mnemonics.emplace_back("LD  V" + std::to_string((currOpcode & 0x0F00) >> 8) + std::string(", [I]")); break;
			default: break;
			}
		}
		break;
		default:
			mnemonics.emplace_back("ILLEGAL OPCODE");

		}
	}

	uint16_t pc = 0x200;
	for (auto &i : mnemonics)
	{
		i = stohex(pc, "0x") + "  " + i;
		pc += 2;
	}
}