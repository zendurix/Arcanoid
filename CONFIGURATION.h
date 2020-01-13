#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

#ifdef _DEBUG
	#define DEBUG 1
#else 
	#define DEBUG 0
#endif

#if DEBUG
	#define LOG(x) std::cout << x << std::endl
#else // if not debug mode - don't print debug logs to console
	#define LOG(x) 
#endif

//#if defined _WIN32  // if compiled(!) on Windows
//	#include "windows.h"
//	#define HIDE_CONSOLE() ShowWindow(GetConsoleWindow(), SW_HIDE)
#//else
	#define HIDE_CONSOLE()
//#endif


enum ePowerType  { guns, platformBig, platformSmall, platfSpeedUp, platfSpeedDown, ballSpeedUp, ballSpeedDown, ballx3 };
enum eEntityType { platformEnt, wallEnt, circleEnt, blockEnt, powerUpEnt, bulletEnt };
enum eDirections { stop = 0, up, down, left, right, upLeft, upRight, downLeft, downRight, backToMenu };
enum eCollision  { noCollision = 0, lineCollision, pointCollision };
enum eMenuOpt    { newGame = 0, continueOpt, help, exitOpt, noOption };

const int WINDOW_LENGTH = 1000;
const int WINDOW_HEIGHT = 700;
const int WINDOW_RIGHT_BORDER = 240;


const int BLOCK_SIZE = 60;
const int SPACE_BETWEEN_BLOCKS = 6;

const int PLATFORM_HEIGHT = 15;

const int FRAMES_PER_SECOND = 60; // MAX
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int TICKS_PER_FRAME = 5;

const int WALL_THICK = 12;

const int PLAYER_START_HP = 5;

const int BULLETS_WAIT = 100;



class MyColors
{
public:
	inline static const sf::Color gold   = sf::Color(255, 215, 0);
	inline static const sf::Color silver = sf::Color(192, 192, 192);
	inline static const sf::Color grey   = sf::Color(128, 128, 128);
};