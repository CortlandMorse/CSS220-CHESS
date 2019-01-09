//Courtney King, Cortland Morse, and  Elizabeth Mathew (cking61 and emathew4)
//Function file for Chess game

#include "Chess.h"
using std::pair;
using std::string;
/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess( void ) : _turn_white( true )
{
	// Add the pawns
	for( int i=0 ; i<8 ; i++ )
	{
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+1 ) , 'P' );
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+6 ) , 'p' );
	}

	// Add the rooks
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+7 ) , 'r' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+7 ) , 'r' );

	// Add the knights
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+7 ) , 'n' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+7 ) , 'n' );

	// Add the bishops
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+7 ) , 'b' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+7 ) , 'b' );

	// Add the kings and queens
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+0 ) , 'Q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+0 ) , 'K' );
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+7 ) , 'q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::path_clear(std::pair<char, char> start, std::pair<char, char> end) { 
  const  Piece* beg= _board(start);
  const char begC = std::get<0>(start);
  const char begR = std::get<1>(start);
  const char endC = std::get<0>(end);
  const char endR = std::get<1>(end);
  int cond;
  if (begR == endR) {
    cond = 1;
  } else if (begC == endC) {
    cond = 2;
  } else {
    cond = 3;
  }
  std::pair< char , char > area;
  char piece = beg->to_ascii();
  if((piece == 'P' || piece == 'p' || piece == 'n' || piece == 'N' || piece == 'K' || piece == 'k' )) {
    return true;
  }
  else {
    switch (cond) {
      case (1): //same row (move L or R)
      for(int i = 1; i < endC - begC; i++) {
        if((endC - begC) > 0) {
          area = std::make_pair( endC + i , begR);
        } else {
          area = std::make_pair( endC - i , begR);
        }
        const Piece* temp = _board(area);
        if( temp != nullptr) {
          return false;
        }
      }
      return true;
      break;
    case (2): //up/down
      for(int i = 1; i < endR - begR; i++) {
        if((endR - begR) > 0) {
          area = std::make_pair( endC, begR + i);
        }
        else {
          area = std::make_pair( endC , begR - i);
        }
        const Piece* temp = _board(area);
        if( temp != nullptr) {
          return false;
        }
      }
      return true;
      break;
    default: //diagonal 
      int lenV = endR - begR;
      int lenH = endC - begC;
      int len = endR - begR;
      for(int i = 1; i < len; i++) {
        if(lenH > 0 && lenV > 0) {
          area = std::make_pair( endC + i , begR + i);
        }
        else if (lenH < 0 && lenV < 0) {
          area = std::make_pair( endC - i , begR - i);
        }
        else if (lenH < 0 && lenV > 0) {
          area = std::make_pair( endC - i , begR + i);
        }
        else {
          return false;
        }
        const Piece* check = _board(area);
        if( check != nullptr) {
          return false;
        }
      }
      return true;
      break;
    }
    return false;
  }
}

bool Chess::make_move( std::pair< char , char > start , std::pair< char , char > end ) {
	
	start.first = std::toupper(start.first);
	start.second = std::toupper(start.second);
	end.first = std::toupper(end.first);
	end.second = std::toupper(end.second);
	
   const Piece* st = _board(start);
   const Piece* en = _board(end);
   if (st == nullptr) {
      std::cout << "Invalid Move" << std::endl;
      return false;
   }
   
   char piece = st->to_ascii();  
   bool st_color = st->is_white();
   bool en_color;
   bool in_check_test = false;
   
   if (en != nullptr) {
      en_color = en->is_white();
	  if (en->to_ascii() == 'K' || en->to_ascii() == 'k') {
		  in_check_test = true;
		}
	}
   
    if (!in_check_test){
		Chess ccopy(*this);
		ccopy._board.remove_piece(start);
        ccopy._board.remove_piece(end);
        ccopy._board.add_piece(end,piece);
		if (ccopy.in_check(st_color)) {
			return false;
		}
	}
	
   //right color being moved
   if (st_color != turn_white()) {
	   return false;
   }
   //DEBUG
   
   //DEBUG
  // there is a piece at end!! 
   if (en != nullptr) {
    //means capturing is happening!!!
    //if the colors are the same--- FALSE
      if(st_color == en_color) {
         return false;
      } else if (st->to_ascii() == 'P' || st->to_ascii() == 'p') {
		  if (st->legal_capture_shape(start,end) && path_clear(start,end)) {
			  if (st->to_ascii() == 'P' && start.second == '7') {
				  piece = 'Q';
			  } else if (st->to_ascii() == 'p' && start.second == '2') {
				  piece = 'q';
			  }
            _board.remove_piece(start);
            _board.remove_piece(end);
            _board.add_piece(end,piece);      
            if(_turn_white) {
               _turn_white = false;
            }
            else {
               _turn_white = true;
            }
            return true;
         }
	  }
      else {
         if (st->legal_move_shape(start,end) && st->legal_capture_shape(start,end) && path_clear(start,end)) {
            if (st->to_ascii() == 'P' && start.second == '7') {
				  piece = 'Q';
			  } else if (st->to_ascii() == 'p' && start.second == '2') {
				  piece = 'q';
			  }
			_board.remove_piece(start);
            _board.remove_piece(end);
            _board.add_piece(end,piece);      
            if(_turn_white) {
               _turn_white = false;
            }
            else {
               _turn_white = true;
            }
            return true;
         }
      }
   }	
   else if (en == nullptr) {
      if (st->legal_move_shape(start,end) && path_clear(start,end)) {
      //if (path_clear(start,end)) {
		  if (st->to_ascii() == 'P' && start.second == '7') {
				  piece = 'Q';
			  } else if (st->to_ascii() == 'p' && start.second == '2') {
				  piece = 'q';
			  }
         _board.remove_piece(start);
         _board.add_piece(end,piece);
         if(_turn_white) {
            _turn_white = false;
         }
         else {
            _turn_white = true;}	    
         return true;
      }
   }
   return false;
}

bool Chess::in_check( bool white ) const {
	Chess ccopy(*this);
	std::pair<char, char> whiteKing;
    std::pair<char, char> blackKing;
	for(char row = 'A'; row <= 'H'; row++) {
      for (char col = '1'; col <= '8'; col++) {
         std::pair<char, char> pos = std::make_pair(row, col);
         if (ccopy._board(pos) != NULL) {
            if (ccopy._board(pos)->to_ascii() == 'K') {
               whiteKing = pos;
            }
            if (ccopy._board(pos)->to_ascii() == 'k') {
               blackKing = pos;
            }
         }
      }
   }
   
   std::pair<char, char> king;
   if (white) {
	   king = whiteKing;
   } else {
	   king = blackKing;
   }	   
	
	for (char row = 'A'; row <= 'H'; row++) {
		for (char col = '1'; col <= '8'; col++) {
			Chess ccopy(*this);
			std::pair<char, char> pos = std::make_pair(row, col);
			const Piece* check = ccopy._board(pos);
			if (check == NULL || (check->is_white() == white)) {
			} else {
				ccopy._turn_white = !turn_white();
				if (ccopy.make_move(pos,king)) {
					return true;
				}
			}
		}
	}
	
	return false;
}

bool Chess::in_mate( bool white ) const {
	if (in_check(white) && in_stalemate(white)) {
		return true;
	}
	
	return false;
}


bool Chess::in_stalemate( bool white ) const {
	Chess ccopy(*this);
	
	for (char row = 'A'; row <= 'H'; row++) {
		for (char col = '1'; col <= '8'; col++) {
			Chess ccopy(*this);
			std::pair<char, char> pos = std::make_pair(row, col);
			const Piece* check = ccopy._board(pos);
			if (check == NULL || (check->is_white() != white)) {
			} else {
				for (char row2 = 'A'; row2 <= 'H'; row2++) {
					for (char col2 = '1'; col2 <= '8'; col2++) {
						Chess ccopy(*this);
						std::pair<char, char> pos2 = std::make_pair(row2, col2);
						if (ccopy.make_move(pos,pos2)) {
							if (!ccopy.in_check(white)) {
								return false;
							}
						}
					}
				}
			}
		}
	}
		
	return true;
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator << ( std::ostream& os , const Chess& chess )
{
	// Write the board out and then either the character 'w' or the character 'b', depending on whose turn it is
	return os << chess.board() << ( chess.turn_white() ? 'w' : 'b' );
}

std::istream& operator >> ( std::istream& is , Chess& chess ) {
	std::pair<char, char> index;
    char let =  'A';
    char num = '8';
    char maxlet = 'H';
    char minnum = '1';
    char temp;
    chess._board.clear_board();	
    for (num = '8'; num >= '1'; num--) {
      for (let = 'A'; let <= 'H'; let++) {
	if(is >> temp) {
	  index = std::make_pair(let,num);
	  //Piece* pt = chess._board.create_piece(temp);
	  if (temp != '-') {
	    if(!chess._board.add_piece(index, temp)) {
	      //return is;	
	    }
	  }
	} 
	else {
	  //return is;
	}
      }
    }
    
   is >> temp;
   if (temp == 'w') {
	   chess._turn_white = true;
   } else {
	   chess._turn_white = false;
   }
   
   return is;
}

