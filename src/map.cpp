#include "map.hpp"
#include "texture.hpp"

int boardMap[8][8] =
    {
        {1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1},
        {1, 2, 1, 2, 1, 2, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1},
};

Map::Map()
{
    whiteSquare = TextureManager::LoadTexture("./assets/whitesquare.png");
    blackSquare = TextureManager::LoadTexture("./assets/blacksquare.png");

    LoadMap(boardMap);

    rectSource = {0, 0, 32, 32};
    rectDestination = {0, 0, 64, 64};
}

void Map::LoadMap(int array[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            map[row][column] = array[row][column];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            type = map[row][column];

            rectDestination.x = column * 64;
            rectDestination.y = row * 64;

            enum
            {
                white = 1,
                black = 2
            };

            switch (type)
            {
            case white:
                TextureManager::Draw(whiteSquare, rectSource, rectDestination);
                break;
            case black:
                TextureManager::Draw(blackSquare, rectSource, rectDestination);
                break;
            default:
                break;
            }
        }
    }
}
