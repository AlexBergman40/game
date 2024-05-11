#include "boardrep.hpp"

void boardrep::updatePossibleMoves(string operation)
{
  // TODO: finish updatePossibleMoves logic

  if (operation == "clear")
  {
    possibleMoves = 0;
    std::cout << "cleared possible moves" << std::endl;
    return;
  }
  // switch
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
  }
}