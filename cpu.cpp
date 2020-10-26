#include "cpu.h"
#include <iostream>
#include <ctime>

Cpu::Cpu(SDL_Surface *scr)
{
    screen = scr;
    srand(time(0));

    //initialisation des composants
    AdressI = 0;
    for (int i=0; i<16; i++)
        Registers[i] = 0;
    PC = 0x200;
    for (int i=0; i<=0xFFF; i++)
        Ram[i] = 0;

    //charge le fontset
    uint8_t fonts [80] =
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
    for (int i=0; i<80; i++)
        fontset[i] = fonts[i];
    for (int i=0; i<0x200; i++)
        Ram[i] = fontset[i];

    //initialise les touches
    for (uint8_t i=0x1; i<=0xF ; i++)
        keys[i] = false;

    //charge la rom
    load_rom("./game.c8");

    //debug le contenu du ram dans un ficher
    ofstream Romdump("./dump");
    for (uint16_t i=0x200; i<0xFFF; i++)
        Romdump << Ram[i];

    //initialise display
    for(int i=0; i < 64; i++)
        for(int j=0; j < 32; j++)
        {
            display[i][j]=0x0;
            buffer[i][j] = display[i][j];
        }
    draw = false;
}

void Cpu::load_rom(char *filename)
{
    ifstream Rom(filename, ios::binary | ios::ate);
    if (Rom.is_open())
    {
        long size = Rom.tellg();
        char *buff = new char [size];
        Rom.seekg(0,ios::beg);
        Rom.read(buff,size);
        Rom.close();
        for (int i=0;i<=size;i++)
            Ram[i+512] = buff[i];
        delete buff;
    }
}

void Cpu::reset()
{
    AdressI = 0;
    for (int i=0; i<16; i++)
        Registers[i] = 0;
    PC = 0x200;
    for (int i=0; i<=0xFFF; i++)
        Ram[i] = 0;

    //charge le fontset
    for (int i=0; i<0x200; i++)
        Ram[i] = fontset[i];

    //charge la rom
    ifstream Rom("./game");
    for (int i=0x200; i<=0xFFF; i++)
    {
        char tmp;
        Rom.get(tmp);
        Ram[i] = tmp;
    }
    clear_screen();
}

void Cpu::decrease_timers()
{
    if (delay_timer > 0)
        delay_timer --;
    if (sound_timer > 0)
    {
        sound_timer --;
        //TODO: ADD BEEP
    }
}

void Cpu::get_inputs()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_0:
                keys[0x0] = true;
                break;
            case SDLK_1:
                keys[0x1] = true;
                break;
            case SDLK_2:
                keys[0x2] = true;
                break;
            case SDLK_3:
                keys[0x3] = true;
                break;
            case SDLK_4:
                keys[0xC] = true;
                break;
            case SDLK_q:
                keys[0x4] = true;
                break;
            case SDLK_w:
                keys[0x5] = true;
                break;
            case SDLK_e:
                keys[0x6] = true;
                break;
            case SDLK_r:
                keys[0xD] = true;
                break;
            case SDLK_a:
                keys[0x7] = true;
                break;
            case SDLK_s:
                keys[0x8] = true;
                break;
            case SDLK_d:
                keys[0x9] = true;
                break;
            case SDLK_f:
                keys[0xE] = true;
                break;
            case SDLK_z:
                keys[0xA] = true;
                break;
            case SDLK_x:
                keys[0x0] = true;
                break;
            case SDLK_c:
                keys[0xB] = true;
                break;
            case SDLK_v:
                keys[0xF] = true;
                break;
            case SDLK_ESCAPE:
                exit(1);
                break;
            }
            break;
        }
        case SDL_KEYUP:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_0:
                keys[0x0] = false;
                break;
            case SDLK_1:
                keys[0x1] = false;
                break;
            case SDLK_2:
                keys[0x2] = false;
                break;
            case SDLK_3:
                keys[0x3] = false;
                break;
            case SDLK_4:
                keys[0xC] = false;
                break;
            case SDLK_q:
                keys[0x4] = false;
                break;
            case SDLK_w:
                keys[0x5] = false;
                break;
            case SDLK_e:
                keys[0x6] = false;
                break;
            case SDLK_r:
                keys[0xD] = false;
                break;
            case SDLK_a:
                keys[0x7] = false;
                break;
            case SDLK_s:
                keys[0x8] = false;
                break;
            case SDLK_d:
                keys[0x9] = false;
                break;
            case SDLK_f:
                keys[0xE] = false;
                break;
            case SDLK_z:
                keys[0xA] = false;
                break;
            case SDLK_x:
                keys[0x0] = false;
                break;
            case SDLK_c:
                keys[0xB] = false;
                break;
            case SDLK_v:
                keys[0xF] = false;
                break;
            }
            break;
        }
        }
    }
}

void Cpu::run()
{
    bool running = true;
    int executed_opcode = 0;
    while(running)
    {
        curr_opcode = GetNextOpcode();
        get_inputs();
        switch (curr_opcode & 0xF000)
        {
        case 0x0000:
            opcode0();
            break;
        case 0x1000:
            opcode1();
            break;
        case 0x2000:
            opcode2();
            break;
        case 0x3000:
            opcode3();
            break;
        case 0x4000:
            opcode4();
            break;
        case 0x5000:
            opcode5();
            break;
        case 0x6000:
            opcode6();
            break;
        case 0x7000:
            opcode7();
            break;
        case 0x8000:
            opcode8();
            break;
        case 0x9000:
            opcode9();
            break;
        case 0xA000:
            opcodeA();
            break;
        case 0xB000:
            opcodeB();
            break;
        case 0xC000:
            opcodeC();
            break;
        case 0xD000:
            opcodeD();
            break;
        case 0xE000:
            opcodeE();
            break;
        case 0xF000:
            opcodeF();
            break;
        default:
            exit(EXIT_FAILURE);
        }
        if (draw)
            draw_on();
        decrease_timers();
        SDL_Delay(1);
        //SDL_Delay(DELAY);
//	if (delay_timer > 0)
//	    delay_timer --;
//	if (sound_timer > 0)
//	    sound_timer --;
    }
}

void Cpu::draw_on()
{
    SDL_Rect rect;
    for (int i=0; i<64; i++)
        for (int j=0; j<32; j++)
        {
            if (display[i][j] ^ buffer[i][j] == 1)
            {
                rect.x = i*10;
                rect.y = j*10;
                rect.w = 10;
                rect.h = 10;
                {
                    if (display[i][j] == 1)
                        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 29, 169, 113));
                    if (display[i][j] == 0)
                        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
                }
            }
        }
    SDL_Flip(screen);
    draw = false;
}

uint16_t Cpu::GetNextOpcode()
{
    uint16_t res = 0;
    res = Ram[PC];
    res <<= 8;
    res |= Ram[PC+1];
    PC += 2;
    return res;
}

void Cpu::clear_screen()
{
    for (int i=0; i<64; i++)
        for (int j=0; j<32; j++)
            display[i][j] = 0x0;
    for (int i=0; i<64; i++)
        for (int j=0; j<32; j++)
        {
            if ( display[i][j] == 1)
                buffer[i][j] = 0;
            else
                buffer[i][j] = 1;
        }
    draw = true;
}

void Cpu::opcode0()
{
    switch(curr_opcode & 0x000F)
    {
    case 0x0000:
        clear_screen();
        draw = true;
        break;
    case 0x000E:
        SP--;
        PC = stack[SP];
        break;
    default:
        break;
    }
}

void Cpu::opcode1()
{
    PC = curr_opcode & 0x0FFF;
}

void Cpu::opcode2()
{
    stack[SP] = PC;
    SP++;
    PC = (curr_opcode & 0x0FFF);
}

void Cpu::opcode3()
{
	int x = curr_opcode & 0x0F00;
	 x >>= 8;
	 uint8_t nn = (uint8_t)curr_opcode & 0x00FF;
	if (Registers[x] == nn)
		PC += 2;
}

void Cpu::opcode4()
{
	int x = curr_opcode & 0x0F00;
	 x >>= 8;
	 int nn = curr_opcode & 0x00FF;
	if (Registers[x] != nn)
		PC += 2;
}

void Cpu::opcode5()
{
	int x = curr_opcode & 0x0F00;
	 x >>= 8;
	int y = curr_opcode & 0x00F0;
	 y >>= 4;
	if (Registers[x] == Registers[y])
		PC += 2;
}

void Cpu::opcode6()
{
	int nn = curr_opcode & 0x00FF;
	int x = curr_opcode & 0x0F00;
	x >>= 8;
	Registers[x] = nn; //Registers[2];
}

void Cpu::opcode7()
{
	int nn = curr_opcode & 0x00FF;
	int x = curr_opcode & 0x0F00;
	x >>= 8;
	Registers[x] += nn;
}

void Cpu::opcode8()
{
	int x = curr_opcode & 0x0F00;
	int y = curr_opcode & 0x00F0;
	switch (curr_opcode & 0x000F)
	{
		case 0x0000:
			x >>= 8;
			y >>= 4;
			Registers[x] = Registers[y];
			break;
		case 0x0001:
			x >>= 8;
			y >>= 4;
			Registers[x] = Registers[x] | Registers[y];
			break;
		case 0x0002:
			x >>= 8;
			y >>= 4;
			Registers[x] = Registers[x] & Registers[y];
			break;
		case 0x0003:
			x >>= 8;
			y >>= 4;
			Registers[x] = Registers[x] ^ Registers[y];
			break;
		case 0x0004:
			x >>= 8;
			y >>= 4;
			if (Registers[x] + Registers[y] > 255)
				Registers[0xF] = 1;
			Registers[x] += Registers[y];
			break;
		case 0x0005:
			x >>= 8;
			y >>= 4;
			if (Registers[x] - Registers[y] < 0)
				Registers[0xF] = 0;
			Registers[x] -= Registers[y];
			break;
		case 0x0006:
			x >>= 8;
			Registers[0xF] = Registers[x] & 0x1;
			Registers[x] >>= 1;
			break;
		case 0x0007:
			x >>= 8;
			y >>= 4;
			if (Registers[y] - Registers[x] < 0)
				Registers[0xF] = 0;
			Registers[x] = Registers[y] - Registers[x];
			break;
		case 0x000E:
			x >>= 8;
			Registers[0xF] = Registers[x] >> 7;
			Registers[x] <<= 1;
			break;
		default:
			break;
	}
}

void Cpu::opcode9()
{
	int x = curr_opcode & 0x0F00;
	x >>= 8;
	int y = curr_opcode & 0x00F0;
	y >>= 4;
	if (Registers[x] != Registers[y])
		PC += 2;
}

void Cpu::opcodeA()
{
    AdressI = curr_opcode & 0x0FFF;
}

void Cpu::opcodeB()
{
    PC = (curr_opcode & 0x0FFF) + Registers[0] ;
}

void Cpu::opcodeC()
{
    int x = (curr_opcode & 0x0F00) >> 8;
    Registers[x] = (rand()% 0xFF) & (curr_opcode & 0x00FF);
}

void Cpu::opcodeD()
{
    uint8_t x = Registers[(curr_opcode & 0x0F00) >> 8];
    uint8_t y = Registers[(curr_opcode & 0x00F0) >> 4];
    uint8_t n = (uint8_t)curr_opcode & 0x000F;
    uint8_t pixel;

    Registers[0xF] = 0;

    for (int i=0; i<64; i++)
        for (int j=0; j<32; j++)
            buffer[i][j] = display[i][j];

    for(int i=0; i < n; i++)
    {
        pixel = Ram[AdressI + i];
        for(int j=0; j < 8; j++)
        {
            if((pixel & (0x80 >> j)) != 0)
            {
                if(display[x+j][y+i] == 1)
                    Registers[0xF] = 1;
                display[x+j][y+i] ^= 1;
            }
        }
    }
    draw = true;
}

void Cpu::opcodeE()
{
    uint8_t x = (curr_opcode & 0x0F00) >> 8;
    switch (curr_opcode & 0x000F)
    {
    case 0x000E:
        if (keys[Registers[x]])
        {
            keys[Registers[x]] = false;
            PC += 2;
        }
        break;
    case 0x0001:
        if (!keys[Registers[x]])
            PC += 2;
        break;
    default:
        break;
    }
}

void Cpu::opcodeF()
{
    uint8_t x = (curr_opcode & 0x0F00) >> 8;
    switch (curr_opcode & 0x000F)
    {
    case 0x0007:
        Registers[x] = delay_timer;
        break;
    case 0x000A:
    {
        bool keypress = false;
        for (uint8_t i=0x1; i <= 0xF; i++)
        {
            if (keys[i])
            {
                keys[i] = false;
                Registers[(curr_opcode & 0x0F00) >> 8] = i;
                keypress = true;
            }
        }
        if (!keypress)
        {
            PC -= 2;
            break;
        }
        else
            break;
    }
    case 0x0005:
    {
        switch (curr_opcode & 0x00FF)
        {
        case 0x0015:
            delay_timer = Registers[x];
            break;
        case 0x0055:
            for (int i=0; i<=x; i++)
                Ram[AdressI+i] = Registers[i];
            AdressI += x + 1;
            break;
        case 0x0065:
            for (int i=0; i<=x; i++)
                Registers[i] = Ram[AdressI+i];
            AdressI += x + 1;
            break;
        default:
            break;
        }
    }
    case 0x0008:
        sound_timer = Registers[x];
        break;
    case 0x000E:
        if (AdressI + Registers[x] > 0xFFF)
            Registers[0xF] = 1;
        else
            Registers[0xF] = 0;
        AdressI += Registers[x];
        break;
    case 0x0009:
        AdressI = Registers[x]*5;
        break;
    case 0x0003:
        Ram[AdressI] = Registers[x]/100;
        Ram[AdressI+1] = (Registers[x]/10) % 10;
        Ram[AdressI+2] = Registers[x] % 10;
        break;
    default:
        break;
    }
}
