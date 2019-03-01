#ifndef SNAKE_CELL_H
#define SNAKE_CELL_H

#include <iostream>


// Base class for snake cell, field cell and other cell types
class Cell 
{
public:

	// the type each cell holds and prints as its content
	using cell_content_type = char;
	explicit Cell(const cell_content_type& = ' ', bool = false, bool prize_ = false); // an empty cell by default

	friend std::ostream& operator<<(std::ostream&os, const Cell& cell);
	
	// if the cell helds something
	bool isOccupied() const { return occupied; }
	void setOccupid(bool o) { occupied = o; }
	bool get_prize() { return prize;  }

	//pure virtual destructor to make this class abstract
	virtual ~Cell() = 0;
protected:

	// whether or not the cell is holds something (part of
	// the snake/border)
	bool occupied;

	// if this cell is edible
	bool prize;


	// each cell prints this when draw method is called
	cell_content_type content;
};

#endif // !SNAKE_CELL_H