#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <vector>
#include <iostream>
#include <memory>
#include "Cell.h"
#include "Field_border_cell.h"



class Field
{
public:
	// friends
	friend std::ostream& operator<<(std::ostream&, const Field&);

	// havind Cell-based objects in this field
	using stored_type = Cell;

	// "matrix" for container
	using field_vector_type = std::vector<std::shared_ptr<stored_type>>;
	using field_container_type = std::vector<field_vector_type>;

	using size_type = field_container_type::size_type;
	// side-length of the square field
	static const size_type field_height = 20;
	static const size_type field_width = 20;
	Field();
	Field(Field&) = delete;

	// being / end
	auto begin() { return container.begin(); }
	auto end() { return container.end(); }

	auto begin() const { return container.begin(); }
	auto end() const { return container.end(); }

	auto cbegin() const { return begin(); }
	auto cend() const { return end(); }

	// swipe the cells within the container
	// intended to be used to move the snake
	void swipe_cells(size_type col1, size_type row1,
		size_type col2, size_type row2);

	void add_to_field(std::shared_ptr<Cell>, size_type, size_type);

	bool cellIsOccupied(size_type, size_type) const;

	field_vector_type& operator[](size_type index)
	{ return container[index]; }

	void reset_cell(size_type, size_type);
private:

	field_container_type container;

	bool isBorder(size_type col, size_type row)
	{
		return (col == 0 || row == 0 
			|| col == field_height - 1 || row == field_width - 1);
	}

	std::shared_ptr<Field_cell> default_field_cell;
	std::shared_ptr<Field_border_cell> default_field_border_cell;
};

#endif // !SNAKE_FIELD_H