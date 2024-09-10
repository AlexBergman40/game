#include "generatePossibleMoves.hpp"
#include <bitset>

// CONSTRUCTOR & DESTRUCTOR

// Default constructor
generatePossibleMoves::generatePossibleMoves() {}

// Initialize with currentPiece, pieceType, and moveHistory
generatePossibleMoves::generatePossibleMoves(const uint64_t &square, const int &pieceType, const std::vector<std::vector<uint64_t>> &moveHistory, const uint64_t &piecesOnBoard, const uint64_t &friendlyPieces, const uint64_t &enemyPieces, std::vector<uint64_t *> pieceTypeContainer)
{
  std::cout << "Generating possible moves for " << pieceType << " at " << std::bitset<64>(square) << std::endl;
  // setting square
  this->square = square;
  this->piecesOnBoard = piecesOnBoard;
  this->friendlyPieces = friendlyPieces;
  this->enemyPieces = enemyPieces;
  this->pieceTypeContainer = pieceTypeContainer;
  this->moveHistory = moveHistory;

  // finding same rank
  uint64_t rank = 0b1111111100000000000000000000000000000000000000000000000000000000;
  for (int i = 0; i < 8; i++)
  {
    if (square & rank)
    {
      sameRank = rank;
      break;
    }
    rank = rank >> 8;
  }

  // calling correct member function
  (this->*funcs[pieceType])();
}

// Destructor
generatePossibleMoves::~generatePossibleMoves() {}

// MEMBER FUNCTION DEFINITIONS
void generatePossibleMoves::recursiveMove(uint64_t recursivePosition, int north, int west)
{
  // limit west/east movement, north/south movement
  if (north == 0 && west == 0) // can't move without any direction
    return;

  uint64_t squareNext = recursivePosition;

  switch (north)
  {
  case 1:
    squareNext = squareNext >> 8;
    break;
  case -1:
    squareNext = squareNext << 8;
    break;
  default:
    break;
  }

  switch (west)
  {
  case 1:
    squareNext = squareNext >> 1;
    break;
  case -1:
    squareNext = squareNext << 1;
    break;
  default:
    break;
  }
  // rook can move up indefinitely
  if (squareNext == 0 /*top and bottom of board*/)
  {
    std::cout << "tried to move vertically off board" << std::endl;
    return;
  }
  if ((recursivePosition & endOfColumn && squareNext & endOfColumn) && west != 0)
  {
    std::cout << "tried to wrap around board" << std::endl;
    return;
  }

  std::cout << std::bitset<64>(squareNext) << std::endl;

  // hits enemy piece => can move to square, but not further
  if (squareNext & enemyPieces)
  {
    possibleMoves |= squareNext;
    return;
  }
  // hits friendly piece => can't move more
  else if (squareNext & friendlyPieces)
    return;
  // has not hit a piece
  else
    possibleMoves |= squareNext;
  recursiveMove(squareNext, north, west);
}

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
  if ((square >> 9) & enemyPieces)
    possibleMoves |= (square >> 9);

  if ((square >> 7) & enemyPieces)
    possibleMoves |= (square >> 7);

  // CHECK EN PASSANT

  uint64_t fifthRank = 0b0000000000000000000000000000000011111111000000000000000000000000;
  if (square & fifthRank)
  {
    uint64_t right = square << 1;
    uint64_t left = square >> 1;

    // check right for pawn => check for previous 2 square move
    std::cout << "           Black Pawns thisrn: " << std::bitset<64>(~moveHistory[moveHistory.size() - 2][BLACKPAWN]) << std::endl;
    if (right & ~leftMostColumn && right & ~moveHistory[moveHistory.size() - 2][BLACKPAWN] && (right >> 16) & ~moveHistory.back()[BLACKPAWN] && (right >> 16) & moveHistory[moveHistory.size() - 2][BLACKPAWN] && right & moveHistory.back()[BLACKPAWN])
    {
      std::cout << "EN PASSANT" << std::endl;
      possibleMoves |= (right >> 8);
    }
    // check left => check for previous 2 square move
    if (left & ~rightMostColumn && left & ~moveHistory[moveHistory.size() - 2][BLACKPAWN] && (left >> 16) & ~moveHistory.back()[BLACKPAWN] && (left >> 16) & moveHistory[moveHistory.size() - 2][BLACKPAWN] && left & moveHistory.back()[BLACKPAWN])
    {
      std::cout << "EN PASSANT" << std::endl;
      possibleMoves |= (left >> 8);
    }
  }
}

void generatePossibleMoves::generateForWhiteRook()
{
  std::cout << "generating for a white rook" << std::endl;
  recursiveMove(square, 1, 0);
  recursiveMove(square, -1, 0);
  recursiveMove(square, 0, 1);
  recursiveMove(square, 0, -1);
}

void generatePossibleMoves::generateForWhiteKnight()
{
  std::cout << "generating for a knight" << std::endl;

  std::vector<uint64_t> knightMoves = {
      (square >> 6),
      (square >> 15),
      (square << 10),
      (square << 17),
      (square << 6),
      (square << 15),
      (square >> 10),
      (square >> 17)};

  for (int i = 0; i < knightMoves.size(); i++)
  {
    int64_t move = knightMoves[i];
    int64_t column, secondMostColumn;
    column = (i > 4) ? rightMostColumn, secondMostColumn = secondRightMostColumn : leftMostColumn, secondMostColumn = secondLeftMostColumn;

    // checking moves for off the board and friendly pieces
    if (move & ~sameRank)
    {
      if (i % 2 == 0) // even i => move is out 2 squares
        if (move & secondMostColumn)
          continue;
        else if (move & column || move & friendlyPieces) // if move is off the board or is friendly)
          continue;
        else
          possibleMoves |= move;
    }
  }
}
void generatePossibleMoves::generateForWhiteBishop()
{
  std::cout << "generating for a white bishop" << std::endl;
  recursiveMove(square, 1, 1);
  recursiveMove(square, 1, -1);
  recursiveMove(square, -1, 1);
  recursiveMove(square, -1, -1);
}
void generatePossibleMoves::generateForWhiteQueen()
{
  std::cout << "generating for a white queen" << std::endl;
  generateForWhiteBishop();
  generateForWhiteRook();
}
void generatePossibleMoves::generateForWhiteKing()
{
  std::cout << "generating for a king" << std::endl;

  std::vector<uint64_t> kingMovesHorizontal = {
      (square >> 7),
      (square << 1),
      (square << 9),
      (square >> 9),
      (square >> 1),
      (square << 7),
  };
  std::vector<uint64_t> kingMovesVertical = {
      (square >> 8),
      (square << 8),
  };

  for (int i = 0; i < kingMovesHorizontal.size(); i++)
  {
    uint64_t move = kingMovesHorizontal[i];
    uint64_t column = (i > 3) ? rightMostColumn : leftMostColumn;
    if (move & column || move & friendlyPieces) // if move is off the board or is friendly
      continue;
    possibleMoves |= move;
  }
  for (uint64_t move : kingMovesVertical)
  {
    if (move == 0 || move & friendlyPieces) // if move is off the board or is friendly
      continue;
    possibleMoves |= move;
  }
}

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
  if ((square << 9) & enemyPieces)
    possibleMoves |= (square << 9);

  if ((square << 7) & enemyPieces)
    possibleMoves |= (square << 7);

  uint64_t fourthRank = 0b0000000000000000000000001111111100000000000000000000000000000000;
  if (square & fourthRank)
  {
    uint64_t right = square << 1;
    uint64_t left = square >> 1;
    if (right & ~leftMostColumn && right & ~moveHistory[moveHistory.size() - 2][WHITEPAWN] && (right << 16) & ~moveHistory.back()[WHITEPAWN] && (right << 16) & moveHistory[moveHistory.size() - 2][WHITEPAWN] && right & moveHistory.back()[WHITEPAWN])
    {
      std::cout << "EN PASSANT" << std::endl;
      possibleMoves |= (right << 8);
    }
    // check left => check for previous 2 square move
    if (left & ~rightMostColumn && left & ~moveHistory[moveHistory.size() - 2][WHITEPAWN] && (left << 16) & ~moveHistory.back()[WHITEPAWN] && (left << 16) & moveHistory[moveHistory.size() - 2][WHITEPAWN] && left & moveHistory.back()[WHITEPAWN])
    {
      std::cout << "EN PASSANT" << std::endl;
      possibleMoves |= (left << 8);
    }
  }
}
void generatePossibleMoves::generateForBlackRook()
{
  generateForWhiteRook();
}
void generatePossibleMoves::generateForBlackKnight()
{
  generateForWhiteKnight();
}
void generatePossibleMoves::generateForBlackBishop()
{
  generateForWhiteBishop();
}
void generatePossibleMoves::generateForBlackQueen()
{
  generateForWhiteQueen();
}
void generatePossibleMoves::generateForBlackKing()
{
  generateForWhiteKing();
}