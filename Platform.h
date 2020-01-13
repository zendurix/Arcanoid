#pragma once

#include "Entity.h"
#include "PowerUp.h"
#include "CONFIGURATION.h"

class Platform : public Entity
{
private:
	int length;
	std::shared_ptr<sf::RectangleShape> rectShape;
	std::vector <PowerUp> activePowerUps;

	bool haveGuns;

public:
	Platform();
	~Platform();

	void update_moveVect(eDirections dir);
	void pick_powerup(PowerUp power);
	void check_powerUps_duration();
	void use_powerUp(bool start, PowerUp power);


	// getters:
	std::shared_ptr<sf::RectangleShape> get_rectShape()   { return rectShape; }
	std::shared_ptr<sf::CircleShape> get_circleShape()    { return nullptr; }
	std::vector <PowerUp> get_activePowerUps()		const {return activePowerUps; }
	int get_length() 								const { return length; }
	bool get_haveGuns()								const { return haveGuns; }

};

