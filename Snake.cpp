#include "Snake.h"
#include <memory>

using std::make_shared;
using std::make_tuple;
using std::get;

Snake::Snake(Field& field_)
	: field(field_)
	, default_snake_cell(make_shared<Snake_cell>())
	, starting_snake_size(3)
{
	size_type height_half = Field::field_height / 2;
	size_type width_half = Field::field_width / 2;

	for (size_type icell = 0; icell != starting_snake_size; ++icell) {
		container.push_back(
			make_tuple(
				default_snake_cell,
				height_half - icell,
				width_half
			)
		);
		// put those `Snake_cell`s into the field
		field.add_to_field(get<0>(container.back()),
			get<1>(container.back()),
			get<2>(container.back())
		);
	}
}

bool Snake::slither(Direction direction)
{
	// the new position we the snake is moving to
	auto newCol = get<1>(container.back());
	auto newRow = get<2>(container.back());


	// update newCol and newRow
	if (!newPos(newCol, newRow, direction)) {
		return true;
	}


	// if the cell we just moved is occupied, the game is over
	// thus, we return false
	if (!pos_is_valid(newCol, newRow)) {
		return false;
	}

	if (field[newCol][newRow]->get_prize())
		grow();


	// if a prize is eaten, move accordingly
	if (waiting_eaten) {
		field.add_to_field(default_snake_cell, newCol, newRow);
		waiting_eaten = false;
	}
	else {
		// swipe the tail and the (empty) cell it is moving to
		field.swipe_cells(newCol, newRow, get<1>(container.front()), get<2>(container.front()));
	}

	// update the position of the cell in snake's own container
	update_cell_pos_info(container.front(), newCol, newRow);

	// move the tail to the back making it the new head
	move_tail_back();

	return true;
}


void Snake::grow()
{
	container.push_front(
		make_tuple(
			default_snake_cell,
			get<1>(container.back()),
			get<2>(container.back())
		)
	);
	waiting_eaten = true;
	ate_this_move = true;
}

// pushes tail to back and pops from front
inline void Snake::move_tail_back()
{
	container.push_back(container.front());
	container.pop_front();
}

// returns true if the position within 
// the field and it is not occupied. false other wise
inline bool Snake::pos_is_valid(size_type col, size_type row)
{
	return col < Field::field_height
		&& row < Field::field_width
		&& !field.cellIsOccupied(col, row);
}

bool Snake::newPos(size_type &newCol, size_type &newRow, Direction direction)
{
	static auto previous = Direction::UP;

	// if the directions are opposite, snake cannot do this move
	if (direction == Direction::CONTINUE || direction == Direction(int(previous) * -1))
		direction = previous;

	// this switch case does the actual movement calculation.
	// There are some moves (like UP when previous was DOWN)
	// that snake cannot do and those have no effect

	switch (direction) {
	case Direction::UP:
		--newCol;
		break;
	case Direction::DOWN:
		++newCol;
		break;
	case Direction::RIGHT:
		++newRow;
		break;
	case Direction::LEFT:
		--newRow;
		break;
	}


	previous = direction;
	return true;
}

// update the cell with new position details in cell_detail_type object
inline void Snake::update_cell_pos_info(cell_detail_type & cdt, size_type col, size_type row)
{
	std::get<1>(cdt) = col;
	std::get<2>(cdt) = row;
}