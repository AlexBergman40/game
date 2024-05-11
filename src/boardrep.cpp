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
    // remove "from" square, bitwise nand with piece integer
    // pieceType ^= from
    // pieceType |= to

    *currentPieceType ^= from;
    *currentPieceType |= to;

    updateCurrentPiece(from, 0);
    updatePiecesOnBoard();

    // add "to" square, bitwise or with piece integer
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

void boardrep::updateCurrentPiece(int64_t square, int LEFTCLICK)
{
    if (!LEFTCLICK) // (RIGHT CLICK) deselect piece, clear possible moves
    {
        currentPiece = 0;
        currentPieceType = nullptr;
        updatePossibleMoves("clear");
        printboard();
        std::cout << "Current piece: " << std::bitset<64>(currentPiece) << std::endl;
        return;
    }

    // (LEFT CLICK) find square at mouse position, if there is a piece present => update current piece and possible moves

    for (int i = 0; i < pieceTypeContainer.size(); i++)
    {
        if (square & *pieceTypeContainer[i])
        {
            currentPiece = square;
            currentPieceType = pieceTypeContainer[i];
            updatePossibleMoves();
        }
    }

    if (currentPiece == square) // current piece updated, possible moves updated
    {
        printboard(); // will highlight the current piece
        std::cout << "Current piece: " << std::bitset<64>(currentPiece) << std::endl;
        std::cout << "Possible moves updated" << std::endl;
    }
}

void boardrep::updatePossibleMoves(string operation)
{
    // TODO: finish updatePossibleMoves logic

    if (operation == "clear")
    {
        possibleMoves = 0;
        printboard();
        std::cout << "cleared possible moves" << std::endl;
        return;
    }
}

void boardrep::updatePiecesOnBoard()
{
    piecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing | whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    whitePiecesOnBoard = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    blackPiecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing;

    // possibly make own updateTurn() function later
    if (whitesTurn)
    {
        friendlyPieces = whitePiecesOnBoard;
        whitesTurn = false;
    }
    else
    {
        friendlyPieces = blackPiecesOnBoard;
        whitesTurn = true;
    }
}

// TODO: check square for action type (select, deselect, move, castling, en passant)
void boardrep::checkSquare(Sint32 x, Sint32 y, int CLICKTYPE)
{
    // if click is off board map:
    // make dust particles

    // if click is on board map:

    // (RIGHT CLICK)
    if (!CLICKTYPE)
    {
        updateCurrentPiece(0, CLICKTYPE);
        return;
    }
    // (LEFT CLICK) find square at mouse position, if there is a piece present => update current piece and possible moves

    int file = x / 64;
    int rank = y / 64;
    int position = rank * 8 + file;
    int64_t square = (int64_t)1 << position;

    if (square & currentPiece && CLICKTYPE) // clicking on the same piece with left click
        return;

    if (square & friendlyPieces)
    {
        updateCurrentPiece(square, CLICKTYPE);
    }
    else if (currentPieceType != nullptr) /*piece type is not null*/
    {
        movePiece(currentPiece, square);
    }
}

void boardrep::drawPossibleMoves()
{
}
