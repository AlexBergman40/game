#include "game.hpp"
#include "texture.hpp"
#include "gameobject.hpp"
#include "map.hpp"
#include "boardrep.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

GameObject *player;
GameObject *enemy;
Map *map;
boardrep *board;

SDL_Renderer *Game::renderer = nullptr;

Game::Game()
{
}
Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    player = new GameObject("./assets/char.png", 100, 100);
    enemy = new GameObject("./assets/enemy.png", 230, 100);
    map = new Map();
    board = new boardrep();
    // using bitboard representation, initialize piece positions
    //
    // white pawns = 8 second rank
    // white castles = 1 bottom left, 1 bottom right
    //
}

void Game::handleEvents()
{
    SDL_Event event;
    int x = 0, y = 0;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            std::cout << "Quitting game!" << std::endl;
            isRunning = false;
            break;

        case SDL_MOUSEMOTION:
            x = event.motion.x;
            y = event.motion.y;
            std::cout << x << ", " << y << std::endl;
            break;

        case SDL_MOUSEBUTTONDOWN: // mouse button is pressed
            if (event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Left mouse button pressed! at: " << event.button.x << ", " << event.button.y << std::endl;
                // board.updateCurrentPiece(event.button.x, event.button.y);
            }
            if (event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_RIGHT)
            {
                std::cout << "Right mouse button pressed! at: " << event.button.x << ", " << event.button.y << std::endl;
            }

        case SDL_MOUSEBUTTONUP:
            if (event.button.state == SDL_RELEASED && event.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Left mouse button released! at: " << event.button.x << ", " << event.button.y << std::endl;
            }
            if (event.button.state == SDL_RELEASED && event.button.button == SDL_BUTTON_RIGHT)
            {
                std::cout << "Right mouse button released! at: " << event.button.x << ", " << event.button.y << std::endl;
            }

        default:
            break;
        }
    }
}

void Game::update()
{
    player->Update();
    enemy->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render here

    map->DrawMap();
    board->printboard();
    player->Render();
    enemy->Render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned!" << std::endl;
}
