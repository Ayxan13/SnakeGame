#include "GamePlay.h"
#include <random>
#include <ctime>
#include <memory>
#include "Prize_cell.h"
#include "Field_cell.h"

using std::cout;
using std::endl;
using std::cin;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::shared_ptr;
using std::make_shared;

GamePlay::GamePlay()
	: field()
	, snake(field)
	, score(0)
	, game_wait_time(0)
{
}

void GamePlay::play()
{
	// opening screen
	initial_display();

	bool move_succeded = true;

	// When prize_counter reaches prize_cnt, a new prize appears
	size_type prize_counter = 0;

	// main game loop
	// the loop goes on until snake.slither returns false

	update_display();
	while (!a_key_pressed()) {
		continue;
	}

	do {
		// if a key is pressed, the snake should move in the 
		// corresponding direction
		if (a_key_pressed()) {
			move_succeded = snake.slither(get_direction(get_pressed_key()));
		}
		// else the snake should continue moving in the previous direction
		else {
			move_succeded = snake.slither(Snake::Direction::CONTINUE);
		}

		// draw the new version of the board
		update_display();

		if (snake.ate_this_move) {
			add_prize_to_field();
			++score;
			snake.ate_this_move = false;
		}

		// wait a little before the next move
		sleep(game_wait_time);
	} while (move_succeded);

	cout << "Game Over" << endl;
}


Snake::Direction GamePlay::get_direction(int ch)
{
	switch (ch) {
	case 'w':
		return Snake::Direction::UP;
	case 's':
		return Snake::Direction::DOWN;
	case 'a':
		return Snake::Direction::LEFT;
	case 'd':
		return Snake::Direction::RIGHT;
	default:
		return Snake::Direction::CONTINUE;
	}
}

inline void GamePlay::update_display()
{
	gotoxy(0, 0);
	std::cout << field;
	std::cout << "Score: " << score << '\n';
}

void GamePlay::add_prize_to_field(size_type prize_amount)
{
	static default_random_engine e(std::time(0));
	static uniform_int_distribution<size_type> dis_height(0, Field::field_height - 1);
	static uniform_int_distribution<size_type> dis_width(0, Field::field_width - 1);
	static std::shared_ptr<Prize_cell> default_prize_cell = make_shared<Prize_cell>();
	static size_type col = 0, row = 0;

	// if we don't find an empty spot in this many tries
	// we just give up
	size_type prize_rand_try_count = Field::field_height * Field::field_width;
	do {
		col = dis_height(e);
		row = dis_width(e);

		if (--prize_rand_try_count == 0) {
			return;
		}
	} while (field.cellIsOccupied(col, row));

	field.add_to_field(default_prize_cell, col, row);
}

void GamePlay::initial_display()
{
	cout << "Welcome to Snake\n";

	cout << "Controls:\n"
		<< "       W\n"
		<< "    A  S  D\n\n\n";

	cout << "Pick enter a speed number between 1 and 10 (larger==faster)" << endl;

	size_type speed_numb = 11;
	cin >> speed_numb;
	while (speed_numb > 10) {
		cout << "This was out of range, plase try again." << endl;
		cin.clear();
		cin >> speed_numb;
	}

	// add 1 to avoid dividing by 0
	++speed_numb;
	// the wait time is the difference in msec
	game_wait_time = 1050 - speed_numb * 100;

	clear_scrn();
}
