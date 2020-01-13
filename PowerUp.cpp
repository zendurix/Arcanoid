#include "PowerUp.h"



PowerUp::PowerUp(ePowerType powerType, int* tickCount, int x, int y) : powerType(powerType)
{
	rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(15, 15));

	if (std::find(POWERS_GOOD.begin(), POWERS_GOOD.end(), powerType) != POWERS_GOOD.end())
	{
		goodPower = true;
		rectShape->setFillColor(sf::Color::Green);
	}
	else if (std::find(POWERS_BAD.begin(), POWERS_BAD.end(), powerType) != POWERS_BAD.end())
	{
		goodPower = false;
		rectShape->setFillColor(sf::Color::Red);
	}
	rectShape->setOutlineColor(sf::Color::White);
	rectShape->setOutlineThickness(2);
	rectShape->setPosition(x, y);
	shape = rectShape;

	entityType = powerUpEnt;

	speed = 1.2;
	circleMoveAngle = -1;
	changedAngle = false;
	movable = true;
	collided = noCollision;
	active = true;

	moveVect = sf::Vector2f(0, speed);

	timeAlive = 0;
}

PowerUp::~PowerUp()
{
}


bool operator == (const PowerUp& first, const PowerUp& second)
{
	if (first.powerType == second.powerType && first.timeAlive == second.timeAlive)
		return true;
	else
		return false;
}