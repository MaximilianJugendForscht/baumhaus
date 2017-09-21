#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"
#include "pieces/CDummyPiece.h"
#include "pieces/PBishop.h"
#include "pieces/PRook.h"
#include "pieces/PKnight.h"
#include "pieces/PPawn.h"
#include "CPipe.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{
  this->toPlay = true; // by default we assume white to play
  for (int r = 0; r < 8; ++r) { // r = rank
    std::vector<CSquare*> rank;
    for (int f = 0; f < 8; ++f) { // f = file
      rank.push_back (new CSquare(r+1, f+1));
    }
    this->squares.push_back(rank);
  }
}

CPos::~CPos()
{
  for (auto rank : this->squares) {
    for (auto square : rank) {
      delete square;
    }
    rank.clear(); // delete the, now, "nullptr"s
  }
  this->squares.clear(); // clear the ranks
}

CPos::CPos(const CPos& other) {
  this->toPlay = other.toPlay;
  for(auto otherRank : other.squares) {
    std::vector<CSquare*> rank;
    for(auto otherSquare : otherRank) {
      rank.push_back(new CSquare(*otherSquare));
    }
    this->squares.push_back(rank);
  }
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"

  switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer(new PKing(true, this)); break;//king
      case 'N': currentSquarePointer -> setPiecePointer(new PKnight(true, this)); break; //knight
      case 'R': currentSquarePointer -> setPiecePointer (new PRook(true, this)); break; //rook
      case 'B': currentSquarePointer -> setPiecePointer (new PBishop(true, this)); break; //bishop
      case 'P': currentSquarePointer -> setPiecePointer (new PPawn(true, this));break; //pawn
      case 'Q': break; //queen
      case 'D': currentSquarePointer -> setPiecePointer (new CDp(true, this)); break;
    //black pieces
      case 'k': currentSquarePointer -> setPiecePointer(new PKing(false, this)); break; //king
      case 'r': currentSquarePointer -> setPiecePointer (new PRook(false, this));break; //rook
      case 'n': currentSquarePointer -> setPiecePointer(new PKnight(false, this)); break; //knight
      case 'b': currentSquarePointer -> setPiecePointer (new PBishop(false, this)); break; //bishop
      case 'p': currentSquarePointer -> setPiecePointer (new PPawn(false, this));break; //pawn
      case 'q': break; //queen

      case 'd': currentSquarePointer -> setPiecePointer (new CDp(false, this)); break;
  }
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::string currentName;
  currentName = fileNames[x-1] + std::to_string(y);
  pipe->d(currentName);
  return (currentName);
}

std::vector <int> CPos::coordFromName (std::string squareName) {
  if (squareName.size() > 2) {
    pipe->d("Error in square Name conversion");
  } else {
    //ok, this is messy, but: we take the character value of the squares character and remove what is before A
    std::vector <int> returnVector;
    returnVector.push_back (squareName [0] -96);
    returnVector.push_back (squareName [1] -48);
    return returnVector;
  }
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
    parseFen(fenI);
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.
  setPiece ('k', getSquarePointer(5, 8)); //hardcoding some pieces in for the time-being
  setPiece ('b', getSquarePointer(6, 8));
  setPiece ('b', getSquarePointer(3, 8));
  setPiece ('r', getSquarePointer(8, 8));
  setPiece ('r', getSquarePointer(1, 8));
  setPiece ('n', getSquarePointer(2, 8));
  setPiece ('n', getSquarePointer(7, 8));
  setPiece ('d', getSquarePointer(4, 8));
  setPiece ('p', getSquarePointer(1, 7));
  setPiece ('p', getSquarePointer(2, 7));
  setPiece ('p', getSquarePointer(3, 7));
  setPiece ('p', getSquarePointer(4, 7));
  setPiece ('p', getSquarePointer(5, 7));
  setPiece ('p', getSquarePointer(6, 7));
  setPiece ('p', getSquarePointer(7, 7));
  setPiece ('p', getSquarePointer(8, 7));
  setPiece ('K', getSquarePointer(5, 1)); //WHITE PIECES
  setPiece ('B', getSquarePointer(6, 1));
  setPiece ('B', getSquarePointer(3, 1));
  setPiece ('R', getSquarePointer(8, 1));
  setPiece ('R', getSquarePointer(1, 1));
  setPiece ('N', getSquarePointer(2, 1));
  setPiece ('N', getSquarePointer(7, 1));
  setPiece ('D', getSquarePointer(4, 1));
  setPiece ('P', getSquarePointer(1, 2));
  setPiece ('P', getSquarePointer(2, 2));
  setPiece ('P', getSquarePointer(3, 2));
  setPiece ('P', getSquarePointer(4, 2));
  setPiece ('P', getSquarePointer(5, 2));
  setPiece ('P', getSquarePointer(6, 2));
  setPiece ('P', getSquarePointer(7, 2));
  setPiece ('P', getSquarePointer(8, 2));
}

CSquare* CPos::getSquarePointer (int x, int y) {
  return squares[y-1][x-1];
}

std::vector <std::string> CPos::getPossibleMoves (bool color) {
  moves.clear();
  loopPieces();
  return moves;
  for (int y = 0; y < squares.size(); y++) {
    for (int x = 0; x < squares[y].size(); x++) {
      pipe->d("  " + str(squares[y][x]->containsPiece()));
    }
    pipe->d("---------------------");
  }
}

void CPos::loopPieces(){
  CSquare *currentSquare;
  CPiece *currentPiece;
  for (int x=1; x<= 8; x++) {
		for (int y=1; y <= 8; y++) { //loops through the entire board
			currentSquare = getSquarePointer(x, y);
			if (currentSquare->containsPiece()) { //if the square contains a piece
				currentPiece = currentSquare->getPiecePointer();
				if (toPlay == true) { //white to play
					if (currentPiece->getColor() == true) { //if the piece is white and white is to play
            appendMoves(currentPiece -> getMoves());
					}
				}
				else { //black to play
					pipe->d("color: " + str(currentPiece->getColor()));
					if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
            appendMoves(currentPiece -> getMoves());
					}
				}
			}
		}
	}
}

void CPos::appendMoves(std::vector <std::string> newMoves) { //appends moves of a single piece to the entire list of Moves.
if (newMoves.size() > 0) {
    moves.insert(moves.end(), newMoves.begin(), newMoves.end());
  }
}

bool CPos::getPlayerColor () {
  return toPlay;
}
