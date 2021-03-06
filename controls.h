#ifndef SNAKE_CONTROLS_H
#define SNAKE_CONTROLS_H

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string_view>    // std::string_view
#include <limits>         // std::numeric_limits

#if defined _WIN32
#define NOMINMAX
#include <conio.h>
#define a_key_pressed() _kbhit()
#define get_pressed_key() _getch()

#define clear_scrn() system("cls")

#include <Windows.h>
inline void gotoxy(short x, short y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)



// Unix-like operating systems are not supported yet
static_assert(false);
#define clear_scrn() system("clear")

int get_pressed_key();
bool a_key_pressed();
inline void gotoxy(short x, short y);

void clear();


#endif // OS check


// Universal tools
inline void sleep(long long msec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

inline void keep_window_open(std::string_view const msg = "Press Enter to continue")
{
	std::cout << msg << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#endif //SNAKE_CONTROLS_H
