//Courtney King and Elizabeth Mathew (cking61 and emathew4)
//Function file for Pawn piece

#include "Pawn.h"
#include "Piece.h" //to use if whit eor black
//function: legal move shape
//
bool Pawn::legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
   char startLet = std::get<0>(start);
   char startNum = std::get<1>(start);
   char endLet = std::get<0>(end);
   char endNum = std::get<1>(end);
  
   int dist = endNum - startNum;
	//can only move forward
   if (startLet == endLet) {
   	//if it is white: 
   	//
      if (is_white()) {
      	//if it starts at beginning row for white
         if (startNum == '2' && dist > 0 && dist <= 2) {
            return true;
         }
         else if (startNum != '2' && dist == 1) {
            return true;
         }
         else {
            return false;
         }
      }
      //if it is black
      else {
         if (startNum == '7' && dist < 0 && dist >= -2) {
            return true;
         }
         else if (startNum != '7' && dist == -1) {
            return true;
         }
         else { 
            return false; 
         }
      }
   }
   return false;
}

bool Pawn::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
   char startLet = std::get<0>(start);
   char startNum = std::get<1>(start);
   char endLet = std::get<0>(end);
   char endNum = std::get<1>(end);


   int vdist = endNum - startNum;
   int hdist = endLet - startLet;
   if (is_white() && vdist == 1 && (hdist == 1 || hdist == -1)) {
      return true;
   }
   else if (!is_white() && vdist == -1 && (hdist == 1 || hdist == -1)) {
      return true;
   }
   return false;
}
