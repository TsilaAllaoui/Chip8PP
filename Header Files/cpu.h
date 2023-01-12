#pragma once

#include <vector>
#include "disassembler.h"
#include <bitset>

// The CPU class of the Chip8
class Cpu
{
	private:
		// The memory of the Chip8
	    uint8_t RAM[4096];

		// Registers (V0 to V15)
	    uint8_t Registers[16];

		// I Register
	    uint16_t I;

		// Program Counter
	    uint16_t PC;

		// Stack Pointer
	    uint16_t SP;

		// The Stack
		std::vector<uint16_t> Stack;

		// Delays Registers
	    uint8_t DT, ST;

		// For the keys inputs
	    std::bitset<16> keys;

		// Buffer of the display
	    uint8_t screenBuffer[64][32];

		// The current opcode
	    uint16_t currOpcode;

	public:

		// Enum for CPU States
		enum STATE {RUNNING, PAUSED, STEP};

		// Constructor
	    Cpu();

		// Destructor
		~Cpu();

		// The length of the Rom file
		static long romFileSize;

		// CPU State
		static STATE state;

		// Chip8 disassembler
		Chip8Disassembler *disassembler;

		// Getters
		uint16_t getPC();
		uint16_t getSP();
		uint16_t getI();
		uint16_t getDT();
		uint16_t getST();
		uint8_t* getRegisters();
		std::map<uint16_t, std::string> getMnemonics();
		std::vector<uint16_t> getStack();

		// Start the CPU
	    void run();

		// Reset the CPU
	    void reset();

		// Fetch current opcode in memory
	    void fetch();

		// Decode and Execute current opcode
		void decodeAndExecute();

		// CPU Step
		void step();

		// Load ROM file into memory
	    void loadRom(std::string filePath);

		// Update timers
		void updateTimers();

		// Set keys states
		void setKeys(std::bitset<16> value);
		void setKey(int i, int value);

		// Get keys states
		std::bitset<16> getKeys();

		// CLS instruction
		void CLS();

		// RET instruction
		void RET();

		// JMP instruction
		void JMP();

		// CALL instruction
		void CALL();

		// SE instruction
		void SE_Vx();

		// SNE instruction
		void SNE_Vx();

		// SE Vx Vy instruction
		void SE_Vx_Vy();

		//LD Vx instruction
		void LD_Vx();

		//ADD Vx instruction
		void ADD_Vx();

		//LD Vx Vy instruction
		void LD_Vx_Vy(int x, int y);

		//OR Vx Vy instruction
		void OR_Vx_Vy(int x, int y);

		//AND Vx Vy instruction
		void AND_Vx_Vy(int x, int y);

		//XOR Vx Vy instruction
		void XOR_Vx_Vy(int x, int y);

		//ADD Vx Vy instruction
		void ADD_Vx_Vy(int x, int y);

		//SUB Vx Vy instruction
		void SUB_Vx_Vy(int x, int y);

		//SUBN Vx Vy instruction
		void SUBN_Vx_Vy(int x, int y);

		//SHR Vx instruction
		void SHR_Vx(int x);

		//SHL Vx instruction
		void SHL_Vx(int x);

		//SNE Vx instruction
		void SNE_Vx_Vy();

		//LD_I instruction
		void LD_I();

		//JP_V0 instruction
		void JP_V0();

		//RND_Vx instruction
		void RND_Vx();

		//DRW_Vx_Vx instruction
		void DRW_Vx_Vy();

		//SKP_Vx instruction
		void SKP_Vx();

		//SKNP_Vx instruction
		void SKNP_Vx();

		//LD_Vx_DT instruction
		void LD_Vx_DT();

		//LD_Vx_k instruction
		void LD_Vx_k();

		//LD_DT_Vx instruction
		void LD_DT_Vx();

		//LD_ST_Vx instruction
		void LD_ST_Vx();

		//ADD_I_Vx instruction
		void ADD_I_Vx();

		//LD_F_Vx instruction
		void LD_F_Vx();

		//LD_B_Vx instruction
		void LD_B_Vx();

		//LD__I__Vx instruction
		void LD__I__Vx();

		//LD__Vx__I instruction
		void LD__Vx__I();
};
