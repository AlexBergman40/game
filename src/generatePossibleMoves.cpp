#include "generatePossibleMoves.hpp"

generatePossibleMoves::generatePossibleMoves(int64_t square, int pieceType)
{
  // setting square
  this->square = square;
  // calling correct member function
  (this->*funcs[pieceType])();
}
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