#pragma once

#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"

class Input
{
private:
	Input() = delete;
	static bool isSet;
public:

	static eDirections input_dir(sf::Event event);
	static char user_input_key(sf::Event event);
	static void set_isSet(bool set) { isSet = set; }
};

