#include "Wall.h"



Wall::Wall(int length, int height, int x, int y)
{
	rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(length, height));
	rectShape->setFillColor(sf::Color::Red);
	rectShape->setPosition(x, y);
	shape = rectShape;

	entityType = wallEnt;

	speed = 0;
	circleMoveAngle = -1;
	changedAngle = 0;
	movable = false;
	collided = noCollision;
	active - true;

	moveVect = sf::Vector2f(0, 0);

	update_prevXY();

}


Wall::~Wall()
{
}
