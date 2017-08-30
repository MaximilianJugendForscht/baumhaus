#include "PKing.h"
#include "../CPos.h"

PKing::PKing(bool colorI, CPos* currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PKing::~PKing()
{
    //dtor
}


std::vector<std::string> PKing::getMoves() {
  std::cout << "getMovesDebug 1" << std::endl;
  std::cout << "coordX=" << cordX << ", coordY=" << cordY << std::endl;
  std::vector <std::string> tempMoves;
  //The moves are hardcoded, as they are constant for a King. PLEASE FORGIVE ME FOR THIS MADNESS!!!
  if (squareAvailable (cordX +1, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+1));
  }
  if (squareAvailable (cordX, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+1));
  }
  if (squareAvailable (cordX -1, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX -1, cordY+1));
  }
  if (squareAvailable (cordX +1, cordY)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY));
  }
  if (squareAvailable (cordX -1, cordY)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY));
  }
  if (squareAvailable (cordX +1, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (squareAvailable (cordX, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1));
  }
  if (squareAvailable (cordX -1, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
  }
  return tempMoves;
}

bool PKing::squareAvailable (int cordX,int cordY) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  std::cout << cordX << ", " << cordY << std::endl;
  if (((cordX > 8) or (cordY > 8)) or ((cordY < 1) or (cordX < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordY, cordX);
    if (currentSquare -> containsPiece() == true) {
      std::cout << "found square containing a piece" << std::endl;
      currentPiece = currentSquare -> getPiecePointer();
      if (currentPiece->getColor() == this->getColor()) {
        result = false;
      }
    }
  }
  return result;
}
