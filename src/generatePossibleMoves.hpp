#include "game.hpp"

class generatePossibleMoves
{
public:
  int64_t generateForWhitePawn();
  int64_t generateForWhiteRook();
  int64_t generateForWhiteKnight();
  int64_t generateForWhiteBishop();
  int64_t generateForWhiteQueen();
  int64_t generateForWhiteKing();
  int64_t generateForBlackPawn();
  int64_t generateForBlackRook();
  int64_t generateForBlackKnight();
  int64_t generateForBlackBishop();
  int64_t generateForBlackQueen();
  int64_t generateForBlackKing();
};