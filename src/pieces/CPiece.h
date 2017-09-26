#ifndef CPIECE_H
#define CPIECE_H

// forward declaration to resolve circular dependancy
class CPos;

#include <string>
#include <vector>
#include <iostream>

//virtual class no instances
class CPiece {
	public:
		void setCoordinates (int cordXI, int cordYI);
		bool getColor();
		virtual std::vector<std::string> getMoves(CPos* currentPos) = 0;
    virtual CPiece* clone() = 0;

	protected:
		int cordX; //the coordinates of the piece.
		int cordY;
		bool color; //the figurine color. True means white. LOL.
};

#endif // CPIECE_H
