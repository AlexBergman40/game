#include "gameobject.hpp"
#include "texture.hpp"
#include <SDL2/SDL_render.h>
#include <cmath>

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(textureSheet);

    xpos = x;
    ypos = y;
    t = x;
}

void GameObject::Update()
{
    t++;
    xpos = ( t % 928 ) - 64;

    double fx = 200 * sin( ( xpos * 3.1415 ) / 100.0) + 320;

    ypos = fx;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = srcRect.h * 2;
    destRect.w = srcRect.w * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
