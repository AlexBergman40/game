#include "game.hpp"
#include "texture.hpp"
#include <cstdint>
#include <string>

using std::string;

class boardrep
{
private:
    // representing pieces in binary, starting at white (bottom), from right to left, from bottom to top, so that bit (binary) traversal is more intuitive
    int64_t blackPawns = 0b0000000000000000000000000000000000000000000000001111111100000000;
    int64_t blackRooks = 0b0000000000000000000000000000000000000000000000000000000010000001;
    int64_t blackKnights = 0b0000000000000000000000000000000000000000000000000000000001000010;
    int64_t blackBishops = 0b0000000000000000000000000000000000000000000000000000000000100100;
    int64_t blackQueens = 0b0000000000000000000000000000000000000000000000000000000000001000;
    int64_t blackKing = 0b0000000000000000000000000000000000000000000000000000000000010000;

    int64_t whitePawns = 0b0000000011111111000000000000000000000000000000000000000000000000;
    int64_t whiteRooks = 0b1000000100000000000000000000000000000000000000000000000000000000;
    int64_t whiteKnights = 0b0100001000000000000000000000000000000000000000000000000000000000;
    int64_t whiteBishops = 0b0010010000000000000000000000000000000000000000000000000000000000;
    int64_t whiteQueens = 0b0000100000000000000000000000000000000000000000000000000000000000;
    int64_t whiteKing = 0b0001000000000000000000000000000000000000000000000000000000000000;

    int64_t piecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing | whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;

    int64_t currentPiece = (int64_t)0; // updates when user selects piece to move, updateCurrentPiece(int64_t piece)
    int currentPieceType = -1;
    int64_t possibleMoves = (int64_t)0; // updates along currentPiece, with updatePossibleMoves(currentPiece)

    SDL_Texture *whitePawnTexture;
    SDL_Texture *blackPawnTexture;
    SDL_Texture *whiteRookTexture;
    SDL_Texture *blackRookTexture;
    SDL_Texture *whiteBishopTexture;
    SDL_Texture *blackBishopTexture;
    SDL_Texture *whiteKnightTexture;
    SDL_Texture *blackKnightTexture;
    SDL_Texture *whiteQueenTexture;
    SDL_Texture *blackQueenTexture;
    SDL_Texture *whiteKingTexture;
    SDL_Texture *blackKingTexture;
    SDL_Texture *highlightTexture;
    SDL_Texture *shadowTexture;

    void movePiece(int64_t from, int64_t to);

public:
    boardrep();
    ~boardrep();

    void checkSquare(Sint32 x, Sint32 y, int LEFTCLICK);
    void printColorPieces(SDL_Texture *pieceTexture, const int64_t &colorPiecePositions);
    void printboard();
    void updateCurrentPiece(Sint32 x, Sint32 y, int highlight);
    void updatePossibleMoves(int64_t piece, int pieceType, int side, string operation = "");
    void updatePiecesOnBoard();

    enum pieceType
    {
        WHITEPAWN,
        WHITEROOK,
        WHITEBISHOP,
        WHITEKNIGHT,
        WHITEQUEEN,
        WHITEKING,
        BLACKPAWN,
        BLACKROOK,
        BLACKBISHOP,
        BLACKKNIGHT,
        BLACKQUEEN,
        BLACKKING
    };

    enum pieces
    {
        PAWN,
        ROOK,
        BISHOP,
        KNIGHT,
        QUEEN,
        KING
    };

    enum sides
    {
        WHITE,
        BLACK
    };
};
