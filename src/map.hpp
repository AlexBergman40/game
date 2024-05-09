#pragma once

#include "game.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int array[20][25]);
    void DrawMap();

private:
    SDL_Rect rectSource, rectDestination;

    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[20][25];
};
