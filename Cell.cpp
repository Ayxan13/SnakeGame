#include "Cell.h"

Cell::Cell(const cell_content_type& content_, bool occupied_, bool prize_)
	: content(content_)
	, occupied(occupied_)
	, prize(prize_)
{ }

Cell::~Cell()
{ }

std::ostream & operator<<(std::ostream & os, const Cell & cell)
{
	os << cell.content;
	return os;
}