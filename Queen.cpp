//Courtney King and Elizabeth Mathew (cking61 and emathew4)
//Function file for Queen piece

#include "Queen.h"

bool Queen::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
   char startLet = std::get<0>(start);
   char startNum = std::get<1>(start);
   char endLet = std::get<0>(end);
   char endNum = std::get<1>(end);

   
   //Bishop Qualities of a Queen
   //calculating the difference between rows and columns                                                                   
   int rowDiff = startNum - endNum;
   int colDiff = startLet - endLet;

   //Cases when difference is negative                                                                                     
   if (rowDiff < 0) {
      rowDiff = rowDiff * -1;
   }
   if (colDiff < 0) {
      colDiff = colDiff * -1;
   }

   if (colDiff == rowDiff) {
      return true;
   }
   else if ((startLet == endLet && startNum != endNum)) {
      return true;
   }
   else if ((startLet != endLet && startNum == endNum)) {
      return true;
   }
   else {
      return false;
   }     
}
