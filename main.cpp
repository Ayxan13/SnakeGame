#include "GamePlay.h"

int main()
{
	while (true) {
		GamePlay gamePlay;
		gamePlay.play();
		
		sleep(100);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Press Q to quit. Press C to continue\n";
		
		int pressed;
		while ( (pressed = get_pressed_key()) != 'q' && pressed != 'c') {
			std::cout << "Press either Q or C\n";
		}
		
		if (pressed == 'q') 
			break;
		clear_scrn();
	}
	
	
	return 0;
}
