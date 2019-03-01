#ifndef SNAKE_GAME_PLAY_H
#define SNAKE_GAME_PLAY_H

#include <iostream>
#include "Field.h"
#include "Snake.h"
#include "Prize_cell.h"
#include "controls.h"

class GamePlay
{
public:
	GamePlay();
	void play();

private:
	using size_type = Field::size_type;

	// How many prize cells have been eaten:
	size_type score;

	// how fast the snake moves: smaller number = faster
	size_type game_wait_time;

	Field field;
	Snake snake;

	// converts a char to direction
	Snake::Direction get_direction(int ch);

	// update the display with new version of the field
	void update_display();


	// create a prize randomly in the field
	void add_prize_to_field(size_type = 1);

	// the opening screen
	void initial_display();
};


#endif // !SNAKE_GAME_PLAY_H