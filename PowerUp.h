#pragma once

#include <algorithm>

#include "Entity.h"
#include "CONFIGURATION.h"
#include "MENU.h"


class PowerUp : public Entity
{
private:
	std::shared_ptr<sf::RectangleShape> rectShape;
	sf::Text text;
	ePowerType powerType;
	int timeAlive;
	bool goodPower;

public:
	PowerUp(ePowerType powerType, int* tickCount, int x, int y);
	~PowerUp();

	static const int PLATFORM_SIZE_CHANGE = 40;
	static const int DURATION_TICKS = FRAMES_PER_SECOND * 12;
	static const int DROP_CHANCE_PERCENT = 45;

	inline static const float PLATFORM_SPEED_CHANGE = 0.2f;
	inline static const float BALL_SPEED_CHANGE = 0.25f;

	inline static const std::vector <ePowerType> POWERS_BAD  = { platformSmall, platfSpeedDown, ballSpeedUp };
	inline static const std::vector <ePowerType> POWERS_GOOD = { guns, platformBig, platfSpeedUp, ballSpeedDown, ballx3 };
	inline static const std::vector <ePowerType> POWERS_ALL  = { guns, platformBig, platformSmall, platfSpeedUp,platfSpeedDown, ballSpeedUp, ballSpeedDown, ballx3 };
	
	friend bool operator == (const PowerUp& first, const PowerUp& second);

	int timeLeft() { return (DURATION_TICKS - timeAlive) / FRAMES_PER_SECOND; }



	std::shared_ptr<sf::RectangleShape> get_rectShape()		  { return rectShape; }
	std::shared_ptr<sf::CircleShape> get_circleShape()		  { return nullptr; }
	int get_timeAlive()									const { return timeAlive; }
	ePowerType get_powerType()							const { return powerType; }
	bool get_goodPower()								const { return goodPower; }

	void set_timeAlive(int set)							 { timeAlive = set; }

	void incr_timeAlive()									{ timeAlive++; }

	bool get_active() { if (active == false || timeAlive > DURATION_TICKS || shape->getPosition().y > WINDOW_LENGTH)  return false;	return true;	 }
};