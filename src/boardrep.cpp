#include "boardrep.hpp"

boardrep::boardrep()
{
    whitePawnTexture = TextureManager::LoadTexture("./assets/whitepawn.png");
    whiteRookTexture = TextureManager::LoadTexture("./assets/whiterook.png");
    whiteKnightTexture = TextureManager::LoadTexture("./assets/whiteknight.png");
    whiteBishopTexture = TextureManager::LoadTexture("./assets/whitebishop.png");
    whiteQueenTexture = TextureManager::LoadTexture("./assets/whitequeen.png");
    whiteKingTexture = TextureManager::LoadTexture("./assets/whiteking.png");
    blackPawnTexture = TextureManager::LoadTexture("./assets/blackpawn.png");
    blackRookTexture = TextureManager::LoadTexture("./assets/blackrook.png");
    blackKnightTexture = TextureManager::LoadTexture("./assets/blackknight.png");
    blackBishopTexture = TextureManager::LoadTexture("./assets/blackbishop.png");
    blackQueenTexture = TextureManager::LoadTexture("./assets/blackqueen.png");
    blackKingTexture = TextureManager::LoadTexture("./assets/blackking.png");
}

boardrep::~boardrep()
{
}

void boardrep::printColorPieces(SDL_Texture* pieceTexture, const int64_t &colorPiecePositions)
{

    /*
    (10011010010 & ( 1 << 4)) >> 4
    (10011010010 & 00000010000) >> 4
    00000010000 >> 4
    00000000001
    */
    int64_t one = 1;
    int xPos = 0;
    int yPos = 0;
    SDL_Rect Src, Dst;
    Src.x = Src.y = 0;
    Src.h = Src.w = 32;
    Dst.h = Dst.w = 64;
    for (int i = 0; i < 64; i++)
    {
        int64_t mask = one << i;
        // 1 = 0b0000000000000000000000000000000000000000000000000000001
        int64_t masked_n = colorPiecePositions& mask;
        if (masked_n != 0)
        {
            xPos = 32 * (i % 8) * 2;
            yPos = 32 * (i / 8) * 2;
            Dst.x = xPos;
            Dst.y = yPos;
            TextureManager::Draw(pieceTexture, Src, Dst);
        }
    }
}

void boardrep::printboard()
{
    printColorPieces(whitePawnTexture, whitePawns);
    printColorPieces(whiteRookTexture, whiteRooks);
    printColorPieces(whiteKnightTexture, whiteKnights);
    printColorPieces(whiteBishopTexture, whiteBishops);
    printColorPieces(whiteQueenTexture, whiteQueens);
    printColorPieces(whiteKingTexture, whiteKing);    
    
    
    printColorPieces(blackPawnTexture, blackPawns);  
    printColorPieces(blackRookTexture, blackRooks);
    printColorPieces(blackBishopTexture, blackBishops);  
    printColorPieces(blackKnightTexture, blackKnights);  
    printColorPieces(blackQueenTexture, blackQueens); 
    printColorPieces(blackKingTexture, blackKing);  
}