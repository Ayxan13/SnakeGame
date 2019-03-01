#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


#include <list>
#include <tuple>
#include "Field.h"
#include "Snake_cell.h"

class Snake
{
public:
	using size_type = Field::size_type;
	Snake(Field&);

	// directions in which snake may move.
	// CONTINUE means keep on going in the 
	// previous direction. Opposite sides are
	// are multiplied by -1
	enum class Direction {
		UP = 1, DOWN = -1,
		LEFT = 2, RIGHT = -2,
		CONTINUE = 3
	};

	Snake(Snake&) = delete;

	// bool slither(Direction) : move snake in the field.
	// Returns false if snake hits something
	// and game should be over. true otherwise
	bool slither(Direction);

	// size of the snake in cells (how many cells
	// it has)
	size_type size() { return container.size(); }

	// a signal to game to create a new prize
	bool ate_this_move = true;

private:
	using cell_ptr = std::shared_ptr<Snake_cell>;
	const size_type starting_snake_size;


	// details about a cell: a (shared) pointer to the cell,
	// column number and row number
	using cell_detail_type = std::tuple<cell_ptr, size_type, size_type>;

	using snake_container_type = std::list<cell_detail_type>;


	Field& field;
	snake_container_type container;

	// called when eaten something causes the snake
	// to grow by 1
	void grow();

	// pushes tail to back and pops from front
	void move_tail_back();

	// returns true if the position within 
	// the field and it is not occupied. false other wise
	bool pos_is_valid(size_type col, size_type row);

	// used by the slither function to get
	// the new col and row pos
	bool newPos(size_type&, size_type&, Direction);

	// update the cell with new position details in cell_detail_type object
	void update_cell_pos_info(cell_detail_type& cdt, size_type col, size_type row);

	std::shared_ptr<Snake_cell> default_snake_cell;

	// if and when a prize is eaten, this becomes true
	// until the snake has moved and is grown accordingly
	bool waiting_eaten = false;
};

#endif // !SNAKE_SNAKE_H
