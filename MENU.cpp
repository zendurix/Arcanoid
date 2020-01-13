#include "MENU.h"

sf::Font* MENU::font = nullptr;

MENU::MENU(sf::RenderWindow* window) : 	windowPtr(window)
{
	if (font != nullptr)
		delete font;
	font = new sf::Font;
	if (!font->loadFromFile("OLORT___.TTF"))
		LOG("ERROR FONT NOT LOADED");

	sf::Text text = init_text();

	text.setString("A");
	charLength = text.getLocalBounds().width;  
	charHeight = text.getLocalBounds().height;

	text.setString("NEW GAME");
	text.setPosition(center_text_posX(text), 200);
	options.push_back(Option{ 0, text, newGame });	

	text.setString("CONTINUE");
	text.setPosition(center_text_posX(text), 300);
	options.push_back(Option{ 1, text, continueOpt });

	text.setString("HELP");
	text.setPosition(center_text_posX(text), 400);
	options.push_back(Option{ 2, text, help });

	text.setString("EXIT");
	text.setPosition(center_text_posX(text), 500);
	options.push_back(Option{ 3, text, exitOpt });

	optionMax = options.size() - 1;
	continueAble = false;
}

MENU::~MENU()
{
	delete font;
}


sf::Text MENU::init_text()
{
	sf::Text text;
	text.setFont(*font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(32);
	return text;
}

eMenuOpt MENU::main_menu()
{
	eMenuOpt option = noOption;
	char input;
	int highlightOpt = 0;

	bool goDown = false;
	bool goUp = false;
	sf::Text title = init_text();
	title.setString("ARCANOID");
	title.setFillColor(sf::Color::Yellow);
	title.setPosition(center_text_posX(title), 30);

	sf::Text subTitle = init_text();
	subTitle.setString("MADE BY MICHAL MAJDA");
	subTitle.setFillColor(sf::Color::Red);
	subTitle.setPosition(center_text_posX(subTitle), 80);

	while (option == noOption)
	{
		goDown = false;
		goUp = false;	
		sf::sleep(sf::milliseconds(10));
		for (Option& opt : options)
		{
			opt.text.setFillColor(sf::Color::White);
		}

		options[highlightOpt].text.setFillColor(sf::Color::Green);
		if (!continueAble)
			options[continueOpt].text.setFillColor(MyColors::grey);

		windowPtr->clear();
		for (Option opt : options)
		{
			windowPtr->draw(opt.text);
		}

		windowPtr->draw(title);
		windowPtr->draw(subTitle);
		windowPtr->display();

		windowPtr->waitEvent(event);
		input = Input::user_input_key(event);

		switch (input)
		{
		case '\n':
		case ' ':	option = options[highlightOpt].retVal;  break;
		case '8':				 goUp = true;				break;
		case '2':				 goDown = true;				break;
		default :											break;
		}		

		if (goDown)		 highlightOpt++;
		else if (goUp)	 highlightOpt--;

		highlightOpt =     (highlightOpt < 0)		? optionMax : highlightOpt;
		highlightOpt = (highlightOpt > optionMax)   ?	  0  	: highlightOpt;

		if (highlightOpt == continueOpt && !continueAble)
		{
			if (goDown)		 highlightOpt++;
			else if (goUp)	 highlightOpt--;
		}
	}
	return option;
}


void MENU::help_option()
{
	text = init_text();
	text.setCharacterSize(24);
	text.setString
	(
		"left \\ right arrows     : navigate platform \n\n"
		//"space				   : pause and unpause game \n\n"
		"escape				  : (in game)back to menu \n\n"
		"\n\n\n\n press anything to continue ..."
	);
	text.setPosition(10, 100);
	windowPtr->clear();
	windowPtr->draw(text);
	windowPtr->display();

	sf::sleep(sf::milliseconds(300));

	windowPtr->pollEvent(event);
	while (event.type != sf::Event::KeyPressed)
	{
		windowPtr->pollEvent(event);
	}
	sf::sleep(sf::milliseconds(300));
}

int MENU::center_text_posX(sf::Text text)
{
	int size = text.getString().getSize();
	int posX = WINDOW_LENGTH / 2 - (size / 2) * (charLength + 1);
	return posX;
}

int MENU::center_text_posY(sf::Text text)
{
	int posY = WINDOW_HEIGHT / 2 -  (charHeight / 2);
	return posY;
}

void MENU::game_over()
{
	text = init_text();
	text.setCharacterSize(32);
	text.setString("YOU DIED");
	text.setFillColor(sf::Color::Red);
	text.setPosition(center_text_posX(text) - WINDOW_RIGHT_BORDER / 2, center_text_posY(text));

	windowPtr->draw(text);
	windowPtr->display();

	continueAble = false;
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		;
	}
	sf::sleep(sf::milliseconds(100));
}


void MENU::win(int points)
{
	text = init_text();
	text.setCharacterSize(32);
	text.setString("VICTORY ACHIEVED");
	text.setFillColor(MyColors::gold);
	text.setPosition(center_text_posX(text) - WINDOW_RIGHT_BORDER / 2, center_text_posY(text));

	windowPtr->draw(text);

	text.setString(std::string("\n\nPoints: " + std::to_string(points)));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(center_text_posX(text) - WINDOW_RIGHT_BORDER / 2, center_text_posY(text));

	windowPtr->draw(text);
	windowPtr->display();

	continueAble = false;
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		;
	}
}