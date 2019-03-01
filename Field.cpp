#include <utility>
#include <iostream>

#include "Field.h"
#include "Field_cell.h"
#include "Field_border_cell.h"


using std::size_t;
using std::make_shared;
using std::cout;
using std::endl;

Field::Field()
	: default_field_cell(make_shared<Field_cell>())
	, default_field_border_cell(make_shared<Field_border_cell>())
{
	// fill in the container with empty `Field_cell`s
	for (size_t icol = 0; icol != field_height; ++icol) {
		container.push_back(field_vector_type());
		for (size_t irow = 0; irow != field_width; ++irow) {
			// if on borders, add a border cell
			// else add a normal field_cell
			container.back().push_back(
				(isBorder(icol, irow) ? default_field_border_cell : default_field_cell)
			);
		}
	}
}



// swipe the cells within the container
// intended to be used to move the snake

void Field::swipe_cells(size_type col1, size_type row1, size_type col2, size_type row2)
{
	std::swap(container[col1][row1], container[col2][row2]);
}

void Field::add_to_field(std::shared_ptr<Cell> cell, size_type col , size_type row)
{
	container[col][row] = cell;
}

bool Field::cellIsOccupied(size_type col, size_type row) const
{
	return container[col][row]->isOccupied();
}

void Field::reset_cell(size_type col, size_type row)
{
	add_to_field(default_field_cell, col, row);
}


std::ostream & operator<<(std::ostream &os, const Field &field)
{
	// for each row
	for (const auto& row : field) {

		// for each element in that row
		for (const auto& elem : row) {
			cout << *elem;
		}

		// break the line after each row
		cout << '\n';
	}

	// finish off drawing the board with 
	// flushing the buffer
	cout << endl;

	return os;
}
