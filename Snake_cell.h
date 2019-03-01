#ifndef SNAKE_SNAKE_CELL_H
#define SNAKE_SNAKE_CELL_H


#include "Cell.h"
class Snake_cell :
	public Cell
{
public:
	Snake_cell();
	~Snake_cell() override = default;
};

#endif // !SNAKE_SNAKE_CELL_H