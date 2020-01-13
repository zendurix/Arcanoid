#include "Input.h"

bool Input::isSet = false;

eDirections Input::input_dir(sf::Event event)
{
	eDirections dir;
	static bool pressedLeft, pressedRight;
	static bool* pressedLater;
	if (!isSet)
	{
		pressedLeft = false;
		pressedRight = false;
		pressedLater = &pressedLeft;
		dir = stop;
		isSet = true;
	}

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			pressedLeft = true;
			pressedLater = &pressedLeft;
			break;
		case sf::Keyboard::Right:
			pressedRight = true;
			pressedLater = &pressedRight;
			break;
		default:
			break;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			pressedLeft = false;
			break;
		case sf::Keyboard::Right:
			pressedRight = false;
			break;
		default:
			break;
		}
	}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	//{
	//		sf::sleep(sf::milliseconds(30));
	//		while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)))
	//			; // wait until space is pressed again
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return backToMenu;

	if (*pressedLater == true)
	{
		if (pressedLater == &pressedLeft)
			dir = left;
		else if (pressedLater == &pressedRight)
			dir = right;
	}
	else
	{
		if (pressedLeft)
			dir = left;
		else if (pressedRight)
			dir = right;
		else
			dir = stop;
	}
	return dir;
}

char Input::user_input_key(sf::Event event)
{
	char input = '\0';
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:	input = '4';	break;
		case sf::Keyboard::Right:	input = '6';	break;
		case sf::Keyboard::Up:		input = '8';	break;
		case sf::Keyboard::Down:	input = '2';	break;
		case sf::Keyboard::Enter:	input = '\n';	break;
		case sf::Keyboard::Space:	input = ' ';	break;
		default:			break;
		}
	}

	return input;
}