#include "game.hpp"
#include <cstdint>
#include <vector>

class generatePossibleMoves
{
private:
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

  static const uint64_t endOfColumn = 0b1000000110000001100000011000000110000001100000011000000110000001;
  static const uint64_t leftMostColumn = 0b0000000100000001000000010000000100000001000000010000000100000001;
  static const uint64_t secondLeftMostColumn = 0b0000001000000010000000100000001000000010000000100000001000000010;
  static const uint64_t rightMostColumn = 0b1000000010000000100000001000000010000000100000001000000010000000;
  static const uint64_t secondRightMostColumn = 0b0100000001000000010000000100000001000000010000000100000001000000;

  uint64_t square = 0;
  std::vector<std::vector<uint64_t>> moveHistory = {};
  uint64_t piecesOnBoard = 0;
  uint64_t friendlyPieces = 0;
  uint64_t enemyPieces = 0;
  uint64_t possibleMoves = 0;
  uint64_t sameRank = 0;

  void recursiveMove(uint64_t square, int north, int west);

  std::vector<uint64_t *> pieceTypeContainer;

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
  generatePossibleMoves(const uint64_t &square,
                        const int &pieceType,
                        const std::vector<std::vector<uint64_t>> &moveHistory,
                        const uint64_t &piecesOnBoard,
                        const uint64_t &friendlyPieces,
                        const uint64_t &enemyPieces,
                        std::vector<uint64_t *> pieceTypeContainer);
  ~generatePossibleMoves();

  uint64_t generate() { return possibleMoves; }
};