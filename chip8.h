#ifndef CHIP8_H
#define CHIP8_H

#include "cpu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define HEIGHT 320
#define WIDHT 640

class Chip8
{
    private:
        SDL_Surface *screen;
    public:
        Chip8();
        void emulate();
};

#endif // CHIP8_H
