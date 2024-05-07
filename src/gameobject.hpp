#pragma once
#include "game.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class GameObject
{

public:

    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:

    int xpos;
    int ypos;
    int t;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

};
