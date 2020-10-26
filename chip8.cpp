#include "chip8.h"

Chip8::Chip8()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *dot;
    screen = SDL_SetVideoMode(WIDHT,HEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_EnableKeyRepeat(1,1);
}

void Chip8::emulate()
{
    Cpu(screen).run();
}
