//Courtney King and Elizabeth Mathew (cking61 and emathew 4)
//Function file for Rook piece

#include "Rook.h"

bool Rook::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
   char startLet = std::get<0>(start);
   char startNum = std::get<1>(start);
   char endLet = std::get<0>(end);
   char endNum = std::get<1>(end);

   //assume that start and end are valid on the board
   //only can move vertically and horizontally
   //MOVING UP OR DOWN
   
   if ((startLet == endLet && startNum != endNum)) {
      return true;
   }
   else if ((startLet != endLet && startNum == endNum)) {
      return true;
   }
   else {
      return false;
   }
}
