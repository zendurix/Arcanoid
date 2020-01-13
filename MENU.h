#pragma once

#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"
#include "Input.h"


class MENU
{
private:
	MENU(sf::RenderWindow* window);
	inline static MENU* instance = nullptr;

	sf::RenderWindow* windowPtr;
	sf::Event event;
	sf::Text text;

	bool continueAble;

	int optionMax;
	float charLength;
	float charHeight;

	struct Option
	{
		int ID;
		sf::Text text;
		eMenuOpt retVal;
	}typedef Option;

	std::vector <Option> options;

public:
	static sf::Font* font;
	static sf::Text init_text();

	static MENU* get_instance(sf::RenderWindow* window) 
	{ 
		if (instance == nullptr) 
			instance = new MENU(window);
		return instance; 
	}
	~MENU();
	

	eMenuOpt main_menu();
	void help_option();
	void game_over();
	void win(int points);
	   
	int center_text_posX(sf::Text text);
	int center_text_posY(sf::Text text);

	void set_continueAble(bool set) { continueAble = set; }
};

