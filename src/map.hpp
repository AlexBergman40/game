#pragma once

#include "game.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int array[8][8]);
    void DrawMap();

private:
    SDL_Rect rectSource, rectDestination;

    SDL_Texture *whiteSquare;
    SDL_Texture *blackSquare;
    SDL_Texture *water;

    int map[8][8];
};
