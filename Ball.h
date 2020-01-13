#pragma once
#include "Entity.h"

#include "CONFIGURATION.h"
#include "Physics.h"
#include "PowerUp.h"


class Ball : public Entity
{
private:
	std::shared_ptr<sf::CircleShape> circleShape;
	std::vector <PowerUp> activePowerUps; 

	inline static std::vector <PowerUp> ballsActivePowerUps; 

public:
	Ball(int x, int y, double angle);
	~Ball();


	void update_moveVect();
	void hit() {};

	void pick_powerup(PowerUp power);
	void check_powerUps_duration();
	void use_powerUp(bool start, PowerUp power);

	// getters:
	inline static std::vector <PowerUp>* get_ballsActivePowerUpsPtr() { return &ballsActivePowerUps; }
	std::shared_ptr<sf::RectangleShape> get_rectShape() { return nullptr; }
	std::shared_ptr<sf::CircleShape> get_circleShape()  { return circleShape; }
	std::vector <PowerUp> get_activePowerUps()			{ return activePowerUps; }
	bool get_active() {
		if (shape->getPosition().y > WINDOW_HEIGHT + 2 ||
			shape->getPosition().y < -3 ||
			shape->getPosition().x > WINDOW_LENGTH - WINDOW_RIGHT_BORDER ||
			shape->getPosition().x < -5) return false; return true; }

};

