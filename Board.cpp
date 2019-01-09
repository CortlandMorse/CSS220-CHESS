//Courtney King and Elizabeth Mathew and Cortland(cking61 and emathew4)

#include <iostream>
#include <utility>
#include <map>
#include <cctype>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board( void ){}

//Copy constructor for Board
Board::Board(const Board& o) {
  for(std::map<std::pair<char, char>, Piece*>::const_iterator it = o._occ.begin(); it != o._occ.end(); ++it) {
    char piece_set = it->second->to_ascii();
    add_piece(it->first, piece_set);
  }
}

const Piece* Board::operator()( std::pair< char , char > pos ) const
{
	if (std::islower(pos.first)) {
		pos.first = std::toupper(pos.first);
	}
	
	if (std::islower(pos.second)) {
		pos.second = std::toupper(pos.second);
	}
	
  std::map<std::pair<char, char>, Piece*>::const_iterator it;
  it = _occ.find(pos);
  if (it == _occ.end()) {
    return NULL;
  }
  else {
    return it->second;
  }
}

bool Board::add_piece( std::pair< char , char > position , char piece_designator ) {
  if((position.first < 'A') || (position.first > 'H')) {
    return false;
  }
  else if((position.second) < '1' || (position.second > '8')) {
      return false;
    }
  else {
    if(_occ.find(position) == _occ.end()) {
      _occ[position] = create_piece(piece_designator);
      return true;
    }
    else {
      return false;
    }
  }
}

bool Board::remove_piece(std::pair<char, char> position) {
  if(position.first < 'A' || position.first > 'H') {
    return false;
  }
  else if(position.second < '1' || position.second > '8') {
    return false;
  }
  else if(_occ.find(position) == _occ.end()) {
    return false;
  }
  else {
    std::map<std::pair<char, char>, Piece*>::iterator it;
    it = _occ.find(position);
    if(it != _occ.end()) {
      delete it->second;
      _occ.erase(it);
      return true;
    }
    else {
      return false;
    }
  }
}
    

bool Board::has_valid_kings( void ) const
{
  int count = 0;
  for(std::map<std::pair<char, char>, Piece*>::const_iterator it  = _occ.cbegin(); it != _occ.cend(); ++it) {
    if(it->second->to_ascii() == ('K') || it->second->to_ascii() == ('k')) {
      count++;
    }
  }

  if(count == 2) {
    return true;
  }
  else {
    return false;
  }
}

void Board::display( void ) const{
	char letter = 'A';
	char number = '8';
	bool check = false;
	bool other = false;

	for(number = '8'; number >= '1'; number--) {
		for(letter = 'A'; letter <= 'H'; letter ++) {
			if(other) {
				Terminal::color_all(true, Terminal::WHITE, Terminal::CYAN);
			} else {
				Terminal::color_all(true, Terminal::WHITE, Terminal::BLACK);
			}
			other = !other;
			for(std::map<std::pair<char, char>, Piece*>::const_iterator it = _occ.cbegin(); it != _occ.cend(); ++it) {
				if((it->first).first == letter && (it->first).second == number) {
					std::cout << " " << it->second->to_ascii() << " ";
					check = true;
				}
			}
			if(!check) {
				std::cout << "   ";
			}
			check = false;
			Terminal::set_default();
		}
		
		other = !other;
		std::cout << std::endl;
		Terminal::set_default();
	}
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator << ( std::ostream& os , const Board& board )
{
	for( char r='8' ; r>='1' ; r-- )
	{
		for( char c='A' ; c<='H' ; c++ )
		{
			const Piece* piece = board( std::pair< char , char >( c , r ) );
			if( piece ) os << piece->to_ascii();
			else        os << '-';
		}
		os << std::endl;
	}
	return os;
}
