#include "game.hpp"
#include <cstdint>
#include <vector>

class generatePossibleMoves
{
private:
  int64_t square = 0;
  int64_t possibleMoves = 0;

  std::vector<void (generatePossibleMoves::*)()> funcs = {
      &generatePossibleMoves::generateForWhitePawn,
      &generatePossibleMoves::generateForWhiteRook,
      &generatePossibleMoves::generateForWhiteKnight,
      &generatePossibleMoves::generateForWhiteBishop,
      &generatePossibleMoves::generateForWhiteQueen,
      &generatePossibleMoves::generateForWhiteKing,
      &generatePossibleMoves::generateForBlackPawn,
      &generatePossibleMoves::generateForBlackRook,
      &generatePossibleMoves::generateForBlackKnight,
      &generatePossibleMoves::generateForBlackBishop,
      &generatePossibleMoves::generateForBlackQueen,
      &generatePossibleMoves::generateForBlackKing,
  };

  void generateForWhitePawn();
  void generateForWhiteRook();
  void generateForWhiteKnight();
  void generateForWhiteBishop();
  void generateForWhiteQueen();
  void generateForWhiteKing();
  void generateForBlackPawn();
  void generateForBlackRook();
  void generateForBlackKnight();
  void generateForBlackBishop();
  void generateForBlackQueen();
  void generateForBlackKing();

public:
  generatePossibleMoves();
  generatePossibleMoves(int64_t square, int pieceType);
  ~generatePossibleMoves();

  int64_t generate() { return possibleMoves; }
};