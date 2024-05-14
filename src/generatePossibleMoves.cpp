#include "generatePossibleMoves.hpp"
#include <bitset>

// CONSTRUCTOR & DESTRUCTOR

// Default constructor
generatePossibleMoves::generatePossibleMoves() {}

// Initialize with currentPiece, pieceType, and moveHistory
generatePossibleMoves::generatePossibleMoves(const int64_t &square, const int &pieceType, const std::vector<std::vector<int64_t>> &moveHistory, const int64_t &piecesOnBoard)
{
  std::cout << "Generating possible moves for " << pieceType << " at " << std::bitset<64>(square) << std::endl;
  // setting square
  this->square = square;
  this->piecesOnBoard = piecesOnBoard;
  // calling correct member function
  (this->*funcs[pieceType])();
}

// Destructor
generatePossibleMoves::~generatePossibleMoves() {}

// MEMBER FUNCTION DEFINITIONS

void generatePossibleMoves::generateForWhitePawn()
{
  std::cout << "generating for a white pawn" << std::endl;

  // check the latest board state for pieces blocking the way
  bool pieceBlockingOneForward = false;
  bool pieceBlockingTwoForward = false;

  if ((square >> 8) & piecesOnBoard)
    pieceBlockingOneForward = true;

  if ((square >> 16) & piecesOnBoard)
    pieceBlockingTwoForward = true;

  if (!pieceBlockingOneForward)
  {
    // pawn can move 1 square forward
    if (square >> 8 != 0) // if square is not off the board
      possibleMoves |= (square >> 8);
    // pawn can move 2 squares forward if it is their first move
    if (!pieceBlockingTwoForward && square & 0b000000011111111000000000000000000000000000000000000000000000000) // pawn is on second rank (hasn't moved)
      possibleMoves |= (square >> 16);
  }
}
void generatePossibleMoves::generateForWhiteRook() {}
void generatePossibleMoves::generateForWhiteKnight() {}
void generatePossibleMoves::generateForWhiteBishop() {}
void generatePossibleMoves::generateForWhiteQueen() {}
void generatePossibleMoves::generateForWhiteKing() {}

void generatePossibleMoves::generateForBlackPawn()
{
  std::cout << "generating for a black pawn" << std::endl;

  // check the latest board state for pieces blocking the way
  bool pieceBlockingOneForward = false;
  bool pieceBlockingTwoForward = false;

  if ((square << 8) & piecesOnBoard)
    pieceBlockingOneForward = true;

  if ((square << 16) & piecesOnBoard)
    pieceBlockingTwoForward = true;

  if (!pieceBlockingOneForward)
  {
    // pawn can move 1 square forward
    if (square << 8 != 0) // if square is not off the board
      possibleMoves |= (square << 8);
    // pawn can move 2 squares forward if it is their first move
    if (!pieceBlockingTwoForward && square & 0b000000000000000000000000000000000000000000000001111111100000000) // pawn is on second rank (hasn't moved)
      possibleMoves |= (square << 16);
  }
}
void generatePossibleMoves::generateForBlackRook() {}
void generatePossibleMoves::generateForBlackKnight() {}
void generatePossibleMoves::generateForBlackBishop() {}
void generatePossibleMoves::generateForBlackQueen() {}
void generatePossibleMoves::generateForBlackKing() {}