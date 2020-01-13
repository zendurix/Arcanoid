#include "Bullet.h"



Bullet::Bullet(int x, int y)
{
	rectShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(9, 9));
	rectShape->setFillColor(MyColors::silver);
	rectShape->setPosition(x, y);
	shape = rectShape;

	entityType = bulletEnt;

	speed = 2;
	circleMoveAngle = -1;
	changedAngle = false;
	movable = true;
	collided = noCollision;
	active = true;

	moveVect = sf::Vector2f(0, -speed);
}


Bullet::~Bullet()
{
}
