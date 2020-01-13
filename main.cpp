#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"
#include "Input.h"
#include "GAME.h"
#include "MENU.h"



int main()
{
	HIDE_CONSOLE();

	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Arcanoid");
	sf::Event event;

	MENU* menu = MENU::get_instance(&window);
	eMenuOpt menuOption;

	GAME* game = GAME::get_instance();
	game->set_windowPtr(&window);

	int tickCount = 0;
	int ticksPerSec = 0;

	eDirections platformDir = stop;

	sf::Clock clock;
	sf::Time timer = clock.getElapsedTime();

	while (window.isOpen())
	{
		menuOption = menu->main_menu();
		switch (menuOption)
		{
		case newGame:
			tickCount = 0;
			ticksPerSec = 0;
			game->reset_game();
		case continueOpt:
			menu->set_continueAble(true);
			Input::set_isSet(false);

			while (window.isOpen()) // GAME LOOP ///////////////////////////////////
			{
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)	window.close();
					else									platformDir = Input::input_dir(event);
				}
				if (platformDir == backToMenu)   			break;


				if (ticksPerSec < FRAMES_PER_SECOND)
				{
					game->check_powerUps_duration();
					for (int i = 0; i < TICKS_PER_FRAME; i++)
					{
						game->control_platform(platformDir);
						game->tick();
					}

					if (game->get_playerHP() <= 0)
					{
						menu->game_over();
						break;
					}

					game->display_update();

					tickCount++;
					game->set_tickCounter(tickCount);
					ticksPerSec++;
					sf::sleep(sf::milliseconds(SKIP_TICKS));
				}		


				timer = clock.getElapsedTime();
				if (timer.asMilliseconds() > 1000)
				{
					game->set_fpsCount(ticksPerSec);
					ticksPerSec = 0;
					clock.restart();
				}	
				
				if (game->get_blocksCount() == 0)
				{
					int points = game->get_points();
					points += game->get_playerHP() * 10;
					menu->win(points);
				}
			}	// END OF GAME LOOP ///////////////////////////////////////////////////////
			break;
		case help:
			menu->help_option();
			break;
		case exitOpt:
			window.close();
			break;
		default:
			break;
		}
	}
	delete game;
	return 0;
}

