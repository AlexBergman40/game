#include "game.hpp"
#include "texture.hpp"
#include <cstdint>

class boardrep
{
private:
    // representing pieces in binary, starting at white (bottom), from right to left, from bottom to top
    // top left is the first bit, bottom right is the lasst bit.
    int64_t blackPawns    = 0b0000000000000000000000000000000000000000000000001111111100000000;
    int64_t blackRooks    = 0b0000000000000000000000000000000000000000000000000000000010000001;
    int64_t blackKnights  = 0b0000000000000000000000000000000000000000000000000000000001000010;
    int64_t blackBishops  = 0b0000000000000000000000000000000000000000000000000000000000100100;
    int64_t blackQueens   = 0b0000000000000000000000000000000000000000000000000000000000001000;
    int64_t blackKing     = 0b0000000000000000000000000000000000000000000000000000000000010000;

    int64_t whitePawns    = 0b0000000011111111000000000000000000000000000000000000000000000000;
    int64_t whiteRooks    = 0b1000000100000000000000000000000000000000000000000000000000000000;
    int64_t whiteKnights  = 0b0100001000000000000000000000000000000000000000000000000000000000;
    int64_t whiteBishops  = 0b0010010000000000000000000000000000000000000000000000000000000000;
    int64_t whiteQueens   = 0b0000100000000000000000000000000000000000000000000000000000000000;
    int64_t whiteKing     = 0b0001000000000000000000000000000000000000000000000000000000000000;

    int64_t currentPiece; // updates when user selects piece to move, updateCurrentPiece(int64_t piece)
    int64_t possibleMoves; // updates along currentPiece, with updatePossibleMoves(currentPiece)

    SDL_Texture* whitePawnTexture;
    SDL_Texture* blackPawnTexture;
    SDL_Texture* whiteRookTexture;
    SDL_Texture* blackRookTexture;
    SDL_Texture* whiteBishopTexture;
    SDL_Texture* blackBishopTexture;
    SDL_Texture* whiteKnightTexture;
    SDL_Texture* blackKnightTexture;
    SDL_Texture* whiteQueenTexture;
    SDL_Texture* blackQueenTexture;
    SDL_Texture* whiteKingTexture;
    SDL_Texture* blackKingTexture;

public:
    boardrep();
    ~boardrep();

    void printColorPieces(SDL_Texture* pieceTexture, const int64_t &colorPiecePositions);
    void printboard();
};

