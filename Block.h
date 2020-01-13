#pragma once

#include "Entity.h"

#include "CONFIGURATION.h"

class Block : public Entity
{
private:
	std::shared_ptr<sf::RectangleShape> rectShape;
	int hp;

public:
	Block(int hp, int posX, int posY);
	~Block();
	
	void hit();


	std::shared_ptr<sf::RectangleShape> get_rectShape()   { return rectShape; }
	std::shared_ptr<sf::CircleShape> get_circleShape()    { return nullptr; }
	bool get_active()			{ if (hp <= 0) return false; return true; }


};

