#include "game.hpp"
#include "texture.hpp"
#include <cstdint>
#include <string>
#include <vector>

using std::string;
using std::vector;

class boardrep
{
private:
    bool whitesTurn = true;

    // representing pieces in binary, starting at white (bottom), from right to left, from bottom to top, so that bit (binary) traversal is more intuitive
    uint64_t whitePawns = 0b0000000011111111000000000000000000000000000000000000000000000000;
    uint64_t whiteRooks = 0b1000000100000000000000000000000000000000000000000000000000000000;
    uint64_t whiteKnights = 0b0100001000000000000000000000000000000000000000000000000000000000;
    uint64_t whiteBishops = 0b0010010000000000000000000000000100000000000000000000000000000000;
    uint64_t whiteQueens = 0b0000100000000000000000000000000000000000000000000000000000000000;
    uint64_t whiteKing = 0b0001000000000000000000000000000000000000000000000000000000000000;

    uint64_t blackPawns = 0b0000000000000000000000000000000000000000000000001111111100000000;
    uint64_t blackRooks = 0b0000000000000000000000000000000000000000000000000000000010000001;
    uint64_t blackKnights = 0b0000000000000000000000000000000000000000000000000000000001000010;
    uint64_t blackBishops = 0b0000000000000000000000000000000000000000000000000000000000100100;
    uint64_t blackQueens = 0b0000000000000000000000000000000000000000000000000000000000001000;
    uint64_t blackKing = 0b0000000000000000000000000000000000000000000000000000000000010000;

    vector<uint64_t *> pieceTypeContainer =
        {
            &whitePawns,
            &whiteRooks,
            &whiteKnights,
            &whiteBishops,
            &whiteQueens,
            &whiteKing,
            &blackPawns,
            &blackRooks,
            &blackKnights,
            &blackBishops,
            &blackQueens,
            &blackKing};

    vector<vector<uint64_t>> moveHistory = {{whitePawns, whiteRooks, whiteKnights, whiteBishops, whiteQueens, whiteKing, blackPawns, blackRooks, blackKnights, blackBishops, blackQueens, blackKing}};

    uint64_t piecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing | whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    uint64_t whitePiecesOnBoard = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    uint64_t blackPiecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing;
    uint64_t friendlyPieces = whitePiecesOnBoard; // alternates between white and black pieces on board
    uint64_t enemyPieces = blackPiecesOnBoard;

    uint64_t currentPiece = (uint64_t)0; // updates when user selects piece to move, updateCurrentPiece(int64_t piece)
    uint64_t *currentPieceType = nullptr;
    uint64_t possibleMoves = (uint64_t)0; // updates along currentPiece, with updatePossibleMoves(currentPiece)

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

    void updateCurrentPiece(uint64_t square, int highlight);
    void updatePossibleMoves(string operation = "");
    void drawPossibleMoves();
    void movePiece(uint64_t from, uint64_t to);
    void takePiece(uint64_t square, uint64_t *pieceType);
    void updatePiecesOnBoard();
    void updateTurn();
    void printColorPieces(SDL_Texture *pieceTexture, const uint64_t &colorPiecePositions);
    vector<uint64_t> getBoardState();
    void updateMoveHistory();

public:
    boardrep();
    ~boardrep();

    void printboard();
    void checkSquare(Sint32 x, Sint32 y, int LEFTCLICK);

    enum pieceTypes
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
