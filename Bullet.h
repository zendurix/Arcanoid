#pragma once
#include "Entity.h"

class Bullet :	public Entity
{
private:
	std::shared_ptr<sf::RectangleShape> rectShape;
public:
	Bullet(int x, int y);
	~Bullet();


	std::shared_ptr<sf::RectangleShape> get_rectShape() { return rectShape; }
	std::shared_ptr<sf::CircleShape> get_circleShape()  { return nullptr; }
	bool get_active() { if (get_posY() <= WALL_THICK + 3 || active == false) return false;  return true; }
};

