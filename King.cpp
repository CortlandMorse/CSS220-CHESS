//Courtney King and Elizabeth Mathew (cking61 and emathew4)

#include "King.h"

bool King::legal_move_shape(std::pair< char , char > start , std::pair< char , char > end ) const {
   char startCol = std::get<0>(start);
   char startRow = std::get<1>(start);
   char endCol = std::get<0>(end);
   char endRow = std::get<1>(end);
   bool legalityRow = false;
   bool legalityCol = false;

   //checks if the end row is 1 step away or on the same line and sets legalityRow                      
   if (endRow > startRow) {
      if ((endRow - startRow) == 1) {
         legalityRow = true;
      }
      else {
         legalityRow = false;
      }
   }
   else if (endRow == startRow) {
      legalityRow = true;
   }
   else {
      if ((startRow - endRow) == 1) {
         legalityRow = true;
      }
      else {
         legalityRow = false;
      }
   }

   //checks if the end column is 1 step away or on the same column and sets legality Column             

   if (endCol > startCol) {
      if ((endCol - startCol) == 1) {
         legalityCol = true;
      }
      else {
         legalityCol = false;
      }
   }
   else if (endCol == startCol) {
      legalityCol = true;
   }
   else {
      if ((startCol - endCol) == 1) {
         legalityCol = true;
      }
      else {
         legalityCol = false;
      }
   }

   //checks legality of column and row                                                                  
   if (legalityCol && legalityRow){
      return true;
   }
   else {
      return false;
   }
}
