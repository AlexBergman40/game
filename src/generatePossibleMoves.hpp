#include "game.hpp"
#include <cstdint>
#include <vector>

class generatePossibleMoves
{
private:
  int64_t square = 0;
  std::vector<std::vector<int64_t>> moveHistory = {};
  int64_t piecesOnBoard = 0;
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
  generatePossibleMoves(const int64_t &square, const int &pieceType, const std::vector<std::vector<int64_t>> &moveHistory, const int64_t &piecesOnBoard);
  ~generatePossibleMoves();

  int64_t generate() { return possibleMoves; }
};