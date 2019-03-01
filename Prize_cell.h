#ifndef SNAKE_PRIZE_CELL_H
#define SNAKE_PRIZE_CELL_H

#include "Cell.h"
class Prize_cell :
	public Cell
{
public:
	Prize_cell();
	~Prize_cell() override = default;
};

#endif // !SNAKE_PRIZE_CELL_H