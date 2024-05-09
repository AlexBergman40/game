#include "texture.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    std::cout << "Loading texture " << texture << std::endl;
    SDL_Surface* tempSurface = IMG_Load(texture);
    if(tempSurface)
    {
        std::cout << "Success!" << std::endl;
    }
    else
    {
        std::cout << "Failure." << std::endl;
    }
    SDL_Texture* outputTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return outputTexture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
