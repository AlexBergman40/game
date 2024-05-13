#include "boardrep.hpp"
#include <bitset>

// Loads piece texture assets
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

// TODO: Properly deallocate memory if needed
boardrep::~boardrep()
{
}

// Moves bit information across *currentPieceType to produce movement once redrawn
void boardrep::movePiece(int64_t from, int64_t to)
{
    *currentPieceType ^= from;
    *currentPieceType |= to;

    updateCurrentPiece(from, 0);

    // add "to" square, bitwise or with piece integer
}

// Simple function that removes a piece from a *pieceType.
// This is used in tandem with movePiece to produce a capture.
void boardrep::takePiece(int64_t square, int64_t *pieceType)
{
    *pieceType ^= square;
}

// Finds pieces positions and draws them
void boardrep::printColorPieces(SDL_Texture *pieceTexture, const int64_t &colorPiecePositions)
{

    int xPos = 0;
    int yPos = 0;
    SDL_Rect Src, Dst;
    Src.x = Src.y = 0;
    Src.h = Src.w = 32;
    Dst.h = Dst.w = 64;
    for (int i = 0; i < 64; i++)
    {
        int64_t mask = (int64_t)1 << i;
        bool isPresent = colorPiecePositions & mask;
        // piece present at position
        if (isPresent)
        {
            // draw pieces
            xPos = 64 * (i % 8); // file
            yPos = 64 * (i / 8); // rank
            Dst.x = xPos;
            Dst.y = yPos;
            // highlight current piece underneath piece sprite
            if (mask == currentPiece)
            {
                TextureManager::Draw(highlightTexture, Src, Dst);
            }
            // draw piece sprite
            TextureManager::Draw(pieceTexture, Src, Dst);
        }
    }
}

// Draws all pieces on the baord currently, also draws currentPiece highlights and possibleMove shadows
void boardrep::printboard()
{
    // draw possible moves underneath piece sprites
    if (possibleMoves)
        drawPossibleMoves();
    // draw pieces
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

// Updates current piece to be drawn, as well as other selection related variables (ie. currentPieceType, possibleMoves)
void boardrep::updateCurrentPiece(int64_t square, int LEFTCLICK)
{
    // (RIGHT CLICK) function called with right click: clear currentPiece, currentPieceType, and possibleMoves
    if (!LEFTCLICK)
    {
        currentPiece = 0;
        currentPieceType = nullptr;
        updatePossibleMoves("clear");
        return;
    }

    // (LEFT CLICK) function called with left click: find square at mouse position, if there is a piece present => update current piece, currentPieceType, and possibleMoves

    for (int i = 0; i < pieceTypeContainer.size(); i++)
    {
        if (square & *pieceTypeContainer[i])
        {
            currentPiece = square;
            currentPieceType = pieceTypeContainer[i];
            updatePossibleMoves();
        }
    }
}

// Updates current int64_t piece integers representing different color pieces on the board
void boardrep::updatePiecesOnBoard()
{
    piecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing | whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    whitePiecesOnBoard = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens | whiteKing;
    blackPiecesOnBoard = blackPawns | blackRooks | blackKnights | blackBishops | blackQueens | blackKing;
}

// Oscilates turns between white and black
void boardrep::updateTurn()
{
    updatePiecesOnBoard();
    updateMoveHistory();

    if (whitesTurn)
    {
        friendlyPieces = blackPiecesOnBoard;
        whitesTurn = false;
    }
    else
    {
        friendlyPieces = whitePiecesOnBoard;
        whitesTurn = true;
    }
}

// TODO: Check square for action type (select, deselect, move, castling, en passant)
void boardrep::checkSquare(Sint32 x, Sint32 y, int CLICKTYPE)
{
    // IF CLICK IS OFF BOARD MAP:
    // make dust particles

    // IF CLICK IS ON BOARD MAP:

    // (RIGHT CLICK)
    if (!CLICKTYPE)
    {
        updateCurrentPiece(0, CLICKTYPE);
        return;
    }
    // (LEFT CLICK)

    // find square at mouse position, if there is a friendly piece present => update current piece and possible moves
    int file = x / 64;
    int rank = y / 64;
    int position = rank * 8 + file;
    int64_t square = (int64_t)1 << position;

    // clicking on the same piece with left click => do nothing
    if (square & currentPiece && CLICKTYPE)
        return;
    // clicking on another friendly piece => update current piece and possible moves
    else if (square & friendlyPieces)
        updateCurrentPiece(square, CLICKTYPE);
    // check if legal move
    else if (square & possibleMoves)
    {
        // clicking on a square that's empty or has enemy piece while currentPiece present
        if (currentPiece)
        {
            // check if enemy piece => take piece
            for (int i = 0; i < pieceTypeContainer.size(); i++)
            {
                if (square & *pieceTypeContainer[i])
                {
                    takePiece(square, pieceTypeContainer[i]);
                    break;
                }
            }
            // move piece
            movePiece(currentPiece, square);
            updateTurn();
        }
    }
}

// updates move history vector
void boardrep::updateMoveHistory()
{
    moveHistory.push_back(getBoardState());
    std::cout << "Move history updated" << std::endl;
}

// copies current board state to a vector
vector<int64_t> boardrep::getBoardState()
{
    return vector<int64_t>{whitePawns, whiteRooks, whiteKnights, whiteBishops, whiteQueens, whiteKing, blackPawns, blackRooks, blackKnights, blackBishops, blackQueens, blackKing};
}