#include "boardrep.hpp"
#include <bitset>

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
    highlightTexture = TextureManager::LoadTexture("./assets/highlight.png");
    shadowTexture = TextureManager::LoadTexture("./assets/shadow.png");
}

boardrep::~boardrep()
{
}

void boardrep::movePiece(int64_t from, int64_t to)
{
    // TODO: write move logic
}

void boardrep::printColorPieces(SDL_Texture *pieceTexture, const int64_t &colorPiecePositions)
{

    // finds pieces at i position and draws them
    int xPos = 0;
    int yPos = 0;
    SDL_Rect Src, Dst;
    Src.x = Src.y = 0;
    Src.h = Src.w = 32;
    Dst.h = Dst.w = 64;
    for (int i = 0; i < 64; i++)
    {
        int64_t mask = (int64_t)1 << i; // = 0b00000000000000001, 1 <- i
        int64_t masked_n = colorPiecePositions & mask;
        if (masked_n != 0) // piece at position
        {
            xPos = 32 * (i % 8) * 2; // file
            yPos = 32 * (i / 8) * 2; // rank
            Dst.x = xPos;
            Dst.y = yPos;
            TextureManager::Draw(pieceTexture, Src, Dst);

            // highlight current piece and possible moves
            if (masked_n == currentPiece)
            {
                TextureManager::Draw(highlightTexture, Src, Dst);
            }
            if (masked_n & possibleMoves)
            {
                TextureManager::Draw(shadowTexture, Src, Dst);
            }
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

void boardrep::updateCurrentPiece(Sint32 x, Sint32 y, int LEFTCLICK)
{
    if (!LEFTCLICK) // (RIGHT CLICK) deselect piece, clear possible moves, and clear highlight
    {
        currentPiece = 0;
        currentPieceType = -1;
        updatePossibleMoves(currentPiece, 0, 0, "clear");
        printboard();
        std::cout << "Current piece: " << std::bitset<64>(currentPiece) << std::endl;
        return;
    }

    // (LEFT CLICK) find square at mouse position, if there is a piece present => update current piece and possible moves
    int file = x / 64;
    int rank = y / 64;
    int position = rank * 8 + file;
    int64_t square = (int64_t)1 << position;
    int pieceType;

    if (square & whitePawns)
    {
        currentPiece = square;
        currentPieceType = WHITEPAWN;
        updatePossibleMoves(currentPiece, PAWN, WHITE);
    }
    else if (square & whiteRooks)
    {
        currentPiece = square;
        currentPieceType = WHITEROOK;
        updatePossibleMoves(currentPiece, ROOK, WHITE);
    }
    else if (square & whiteKnights)
    {
        currentPiece = square;
        currentPieceType = WHITEKNIGHT;
        updatePossibleMoves(currentPiece, KNIGHT, WHITE);
    }
    else if (square & whiteBishops)
    {
        currentPiece = square;
        currentPieceType = WHITEBISHOP;
        updatePossibleMoves(currentPiece, BISHOP, WHITE);
    }
    else if (square & whiteQueens)
    {
        currentPiece = square;
        currentPieceType = WHITEQUEEN;
        updatePossibleMoves(currentPiece, QUEEN, WHITE);
    }
    else if (square & whiteKing)
    {
        currentPiece = square;
        currentPieceType = WHITEKING;
        updatePossibleMoves(currentPiece, KING, WHITE);
    }

    if (currentPiece == square) // current piece updated, possible moves updated
    {
        printboard(); // will highlight the current piece
        std::cout << "Current piece: " << std::bitset<64>(currentPiece) << std::endl;
        std::cout << "Possible moves updated" << std::endl;
    }
}

void boardrep::updatePossibleMoves(int64_t currentPiece, int pieceType, int side, string operation)
{
    // TODO: finish updatePossibleMoves logic

    if (operation == "clear")
    {
        possibleMoves = 0;
        printboard();
        std::cout << "cleared possible moves" << std::endl;
        return;
    }

    if (side == WHITE)
    {
        if (pieceType == PAWN)
        {
            if (currentPiece & 0b0000000011111111000000000000000000000000000000000000000000000000) // pawn hasn't moved (second rank)
            {
                possibleMoves = currentPiece >> 8;
                possibleMoves |= currentPiece >> 16;
                possibleMoves &= ~piecesOnBoard;
                printboard();
            }
        }
    }
}

void boardrep::updatePiecesOnBoard()
{
    int64_t piecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing | whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
}

// TODO: check square for action type (select, deselect, move, castling, en passant)
void boardrep::checkSquare(Sint32 x, Sint32 y, int LEFTCLICK)
{
    if (!LEFTCLICK) // (RIGHT CLICK) deselect piece, clear possible moves, and clear highlight
    {
        updateCurrentPiece(x, y, !LEFTCLICK);
    }

    // (LEFT CLICK) find square at mouse position, if there is a piece present => update current piece and possible moves
    updateCurrentPiece(x, y, LEFTCLICK);
}