#include "Platform.h"



Platform::Platform()
{
	length = 120;

	rectShape = std::make_shared<sf::RectangleShape> (sf::Vector2f(length, PLATFORM_HEIGHT));
	rectShape->setFillColor(sf::Color::White);
	rectShape->setPosition(330, WINDOW_HEIGHT - 20);
	shape = rectShape;

	entityType = platformEnt;

	speed = 0.85;
	circleMoveAngle = -1;
	changedAngle = false;
	movable = true;
	collided = noCollision;
	active = true;

	moveVect.y = 0;

	haveGuns = false;	
}


Platform::~Platform()
{
}


void Platform::update_moveVect(eDirections dir)
{
	if (dir == left)
	{
		moveVect.x = -speed;;
	}
	else if (dir == right)
	{
		moveVect.x = speed;
	}
	else // dir == stop
	{
		moveVect.x = 0;
	}
}

void Platform::pick_powerup(PowerUp power)
{
	activePowerUps.push_back(power);
	use_powerUp(true, power);
}

void Platform::check_powerUps_duration()
{
	for (PowerUp &power : activePowerUps)
	{
		power.incr_timeAlive();
	}
	if (activePowerUps.size() > 0)
	{
		while (!activePowerUps.front().get_active())
		{
			PowerUp powerEnded(activePowerUps.front());
			activePowerUps.erase(activePowerUps.begin());
			use_powerUp(false, powerEnded);
		}
	}
}

void Platform::use_powerUp(bool start, PowerUp power)
{
	int mult;
	if (start) mult =  1;
	else	   mult = -1;

	int x = shape->getPosition().x;
	int y = shape->getPosition().y;
	
	switch (power.get_powerType())
	{
	case platformBig:
		length += mult * PowerUp::PLATFORM_SIZE_CHANGE;
		rectShape->setSize(sf::Vector2f(length, PLATFORM_HEIGHT));
		shape->setPosition(x + PowerUp::PLATFORM_SIZE_CHANGE / 2, y);
		break;
	case platformSmall:
		length -= mult * PowerUp::PLATFORM_SIZE_CHANGE;
		rectShape->setSize(sf::Vector2f(length, PLATFORM_HEIGHT));
		shape->setPosition(x - PowerUp::PLATFORM_SIZE_CHANGE / 2, y);
		break;
	case platfSpeedUp:
		speed += mult * PowerUp::PLATFORM_SPEED_CHANGE;
		break;
	case platfSpeedDown:
		speed -= mult * PowerUp::PLATFORM_SPEED_CHANGE;
		break;
	case guns:
		haveGuns = (mult == 1) ? true : false;
		break;
	default:
		break;
	}

	x = shape->getPosition().x;
	while (shape->getPosition().x + length >= WINDOW_LENGTH - (WINDOW_RIGHT_BORDER + WALL_THICK))
	{ // make shure incrased legth platfrom isn't colliding with walls
		x -= 10;
		shape->setPosition(x, y);
	}
	while (shape->getPosition().x <= WALL_THICK + 1)
	{
		x += 10;
		shape->setPosition(x, y);
	}
}