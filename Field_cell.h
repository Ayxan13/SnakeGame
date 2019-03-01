#ifndef SNAKE_FIELD_CELL_H
#define SNAKE_FIELD_CELL_H


#include "Cell.h"
class Field_cell :
	public Cell
{
public:
	// an explicitly empty cell
	explicit Field_cell(const cell_content_type& = ' ', bool = false);
	~Field_cell() override = default;
protected:
	// nothing yet
};

#endif // !SNAKE_FIELD_CELL_H