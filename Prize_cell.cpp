#include "Prize_cell.h"

using std::size_t;

Prize_cell::Prize_cell()
	: Cell('*', false, true)
	// the cell is not occupied although it is not empty
	// because hitting an occupied cell would kill the snake
{ }