#include "Block.h"



Block::Block(int hp, int posX, int posY) : hp(hp)
{
	rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE/3));
	rectShape->setPosition(posX, posY);
	if (hp == 2)			rectShape->setFillColor(sf::Color::Magenta);
	else if (hp == 1)		rectShape->setFillColor(sf::Color::Green);
	shape = rectShape;

	entityType = blockEnt;

	speed = 0;
	circleMoveAngle = -1;
	changedAngle = false;
	movable = false;
	collided = noCollision;
	active = true;

	moveVect = sf::Vector2f(0, 0);
}


Block::~Block()
{
}


void Block::hit()
{
	hp -= 1;
	if (hp == 1)
		rectShape->setFillColor(sf::Color::Green);
}

