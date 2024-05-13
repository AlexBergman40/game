#include "boardrep.hpp"

// TODO: Finish updatePossibleMoves logic
void boardrep::updatePossibleMoves(string operation)
{

  if (operation == "clear")
  {
    possibleMoves = 0;
    drawPossibleMoves();
    return;
  }
  int pieceIndex = 0;
  for (int i = 0; pieceTypeContainer.size(); i++)
  {
    if (currentPieceType == pieceTypeContainer[i])
    {
      pieceIndex = i;
      break;
    }
  }
  switch (pieceIndex)
  {
  case WHITEPAWN:

    break;
  case WHITEROOK:
    break;
  case WHITEKNIGHT:
    break;
  case WHITEBISHOP:
    break;
  case WHITEQUEEN:
    break;
  case WHITEKING:
    break;
  case BLACKPAWN:
    break;
  case BLACKROOK:
    break;
  case BLACKKNIGHT:
    break;
  case BLACKBISHOP:
    break;
  case BLACKQUEEN:
    break;
  case BLACKKING:
    break;

  default:
    break;
  }

  drawPossibleMoves();
}

// Finds and draws possible moves on the board
void boardrep::drawPossibleMoves()
{
  int xPos = 0;
  int yPos = 0;
  SDL_Rect Src = {0, 0, 32, 32},
           Dst = {0, 0, 64, 64};
  for (int i = 0; i < 64; i++)
  {
    int64_t mask = (int64_t)1 << i;
    bool isPresent = possibleMoves & mask;
    // possible move present at i'th square
    if (isPresent)
    {
      // draw shadow
      xPos = 32 * (i % 8) * 2; // file
      yPos = 32 * (i / 8) * 2; // rank
      Dst.x = xPos;
      Dst.y = yPos;

      TextureManager::Draw(shadowTexture, Src, Dst);
    }
  }
}