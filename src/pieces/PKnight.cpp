#include "PKnight.h"
#include "../CPipe.h"
#include "../CPos.h"

CPiece* PKnight::clone(CPos* position) {
  CPiece* clone = new PKnight(this->color, position);

  return clone;
}

PKnight::PKnight(bool colorI, CPos* currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
    if (color) { //if the piece is white, give it a white FEN-Name
      fenType = 'N';
    } else {
      fenType = 'n';
    }
}

PKnight::~PKnight()
{
    //dtor
}


std::vector<std::string> PKnight::getMoves() {
  tempMoves.clear();
  //The moves are hardcoded, as they are constant for a King. PLEASE FORGIVE ME FOR THIS MADNESS!!!
  if (squareAvailable (cordX -2, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX -2, cordY+1));
  }
  if (squareAvailable (cordX -2, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-2, cordY-1));
  }
  if (squareAvailable (cordX +2, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX +2, cordY+1));
  }
  if (squareAvailable (cordX +2, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+2, cordY-1));
  }
  if (squareAvailable (cordX -1, cordY-2)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-2));
  }
  if (squareAvailable (cordX +1, cordY-2)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-2));
  }
  if (squareAvailable (cordX+1, cordY+2)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+2));
  }
  if (squareAvailable (cordX -1, cordY+2)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY+2));
  }
  return tempMoves;
}

bool PKnight::squareAvailable (int cordXI,int cordYI) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  if (((cordXI > 8) || (cordYI > 8)) || ((cordYI < 1) || (cordXI < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordXI, cordYI);
    if (currentSquare -> containsPiece() == true) {
      currentPiece = currentSquare -> getPiecePointer();
      if (currentPiece->getColor() == this->getColor()) {
        result = false;
      } else {
              tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(cordXI, cordYI));
              result = false;
      }
    }
  }
  return result;
}
