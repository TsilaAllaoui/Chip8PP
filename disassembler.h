#pragma once

#include <unordered_map>

// Chip8 disassembler class
class Chip8Disassembler
{
	private:
		// The byte array of the rom
		std::vector<uint8_t> rom;

	public:
		// Constructor and destructor
		Chip8Disassembler(const std::vector<uint8_t> &rom);
		~Chip8Disassembler();

		// Disassemble the rom bytes
		void disassemble();

		// The match of the WORDs to mnemonics 
		std::vector<std::string> mnemonics;
};