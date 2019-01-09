//Courtney King and Elizabeth Mathew (cking61 and emathew4)
//Function file for Knight piece

#include "Knight.h"

bool Knight::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
   char startLet = std::get<0>(start);
   char startNum = std::get<1>(start);
   char endLet = std::get<0>(end);
   char endNum = std::get<1>(end);


   if ((endLet == (startLet + 2))) {
    //move right two paces
      if ((startNum + 1 == endNum) || (startNum - 1 == endNum)) {
         return true;
      }
      else {
         return false;
      }
   }
   else if (endLet == (startLet - 2)){
    //left two spaces
      if ((startNum + 1 == endNum) || (startNum - 1 == endNum)) {
         return true;
      }
      else {
         return false;
      }
   }
   else if (endLet == (startLet + 1)) {
    //right one space
      if ((startNum + 2 == endNum) || (startNum - 2 == endNum)) {
         return true;
      }
      else {
         return false;
      }
   }
   else if (endLet == (startLet - 1)) {
    //moving left one space
      if ((startNum + 2 == endNum) || (startNum - 2 == endNum)) {
         return true;
      }
      else {
         return false;
      }
   }
   else {
      return false;
   }
}

