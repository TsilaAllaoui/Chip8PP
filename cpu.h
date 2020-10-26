#ifndef CPU_H
#define CPU_H

#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <SDL/SDL.h>

#define DELAY 1

using namespace std;

class Cpu
{
	private:
		SDL_Surface *screen;
	    uint8_t Ram[4096];
	    uint8_t Registers[16];
	    uint16_t AdressI;
	    uint16_t PC;
	    uint16_t SP;
	    uint16_t stack[16];
	    uint8_t delay_timer, sound_timer;
	    bool keys[16];
	    uint8_t display[64][32], buffer[64][32];
	    uint16_t curr_opcode;
	    bool draw;
	    uint8_t fontset[80];

	public:
	    Cpu(SDL_Surface *scr);
	    void run();
	    void reset();
	    uint16_t GetNextOpcode();
	    void clear_screen();
	    void draw_on();
	    void decrease_timers();
	    void get_inputs();
	    void load_rom(char *filename);

	    //tous les opcodes

	    void opcode0();
		void opcode1();
	    void opcode2();
	    void opcode3();
	    void opcode4();
	    void opcode5();
	    void opcode6();
	    void opcode7();
	    void opcode8();
	    void opcode9();
	    void opcodeA();
	    void opcodeB();
	    void opcodeC();
	    void opcodeD();
	    void opcodeE();
	    void opcodeF();
};

#endif
