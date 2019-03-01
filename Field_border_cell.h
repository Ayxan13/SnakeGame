#ifndef SNAKE_FIELD_BORDER_CELL_H
#define SNAKE_FIELD_BORDER_CELL_H


#include "Field_cell.h"

// Same as a Field_cell 
// except that this is occupied
// and prints an 'x' instead of ' '
class Field_border_cell :
	public Field_cell
{
public:
	Field_border_cell();
	~Field_border_cell() = default;
};

#endif // !SNAKE_FIELD_BORDER_CELL_H