#pragma once
#include "Entity.h"



class Wall :public Entity
{
private:
	std::shared_ptr<sf::RectangleShape> rectShape;
public:
	Wall(int length, int height, int x, int y);
	~Wall();
	
	std::shared_ptr<sf::RectangleShape> get_rectShape() { return rectShape; }
	std::shared_ptr<sf::CircleShape> get_circleShape()  { return nullptr; }
};

