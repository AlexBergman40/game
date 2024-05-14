#include "generatePossibleMoves.hpp"
#include <bitset>

// constructors & destructor
generatePossibleMoves::generatePossibleMoves() {}
generatePossibleMoves::generatePossibleMoves(int64_t square, int pieceType)
{
  std::cout << "Generating possible moves for " << pieceType << " at " << std::bitset<64>(square) << std::endl;
  // setting square
  this->square = square;
  // calling correct member function
  (this->*funcs[pieceType])();
}
generatePossibleMoves::~generatePossibleMoves() {}

// member function definitions
void generatePossibleMoves::generateForWhitePawn() {}
void generatePossibleMoves::generateForWhiteRook() {}
void generatePossibleMoves::generateForWhiteKnight() {}
void generatePossibleMoves::generateForWhiteBishop() {}
void generatePossibleMoves::generateForWhiteQueen() {}
void generatePossibleMoves::generateForWhiteKing() {}
void generatePossibleMoves::generateForBlackPawn() {}
void generatePossibleMoves::generateForBlackRook() {}
void generatePossibleMoves::generateForBlackKnight() {}
void generatePossibleMoves::generateForBlackBishop() {}
void generatePossibleMoves::generateForBlackQueen() {}
void generatePossibleMoves::generateForBlackKing() {}