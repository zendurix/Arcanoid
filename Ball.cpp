#include "Ball.h"



Ball::Ball(int x, int y, double angle)
{
	circleShape = std::make_shared<sf::CircleShape>(10);
	circleShape->setFillColor(sf::Color::Yellow);
	circleShape->setPosition(x, y);
	shape = circleShape;

	entityType = circleEnt;

	speed = 1;
	circleMoveAngle = angle;
	changedAngle = true;
	movable = true;
	collided = noCollision;
	active = true;

	update_moveVect();
}


Ball::~Ball()
{
}




void Ball::update_moveVect()
{
	if (changedAngle)
	{
		char quarter = Physics::check_angle_quarter(circleMoveAngle);
		float aSide, bSide;						// triangle sides, speed is c - hypotenuse ( PL przeciwprostokatna)
		sf::Vector2f abPoint, acPoint, bcPoint;		// points beetwen sides
		float angle = Physics::degree_to_radian(circleMoveAngle);
		if (angle == 0.0) angle = 2 * PI;

		aSide = sin(angle) * speed;
		bSide = aSide / tan(angle);

		bcPoint = sf::Vector2f(shape->getPosition().x, shape->getPosition().y);
		abPoint = sf::Vector2f(bcPoint.x, bcPoint.y + bSide);
		acPoint = sf::Vector2f(bcPoint.x + aSide, abPoint.y);

		moveVect.x = abs(acPoint.x - bcPoint.x);
		moveVect.y = abs(acPoint.y - bcPoint.y);

		switch (quarter)
		{
		case 1:							 moveVect.y *= (-1); 	break;
		case 2: 								  				break;
		case 3:	moveVect.x  *= (-1);							break;
		case 4:	moveVect.x  *= (-1);	 moveVect.y *= (-1);	break;
		}

		changedAngle = false;
	}
}



void Ball::pick_powerup(PowerUp power)
{
	activePowerUps.push_back(power);
	use_powerUp(true, power);
}

void Ball::check_powerUps_duration()
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

void Ball::use_powerUp(bool start, PowerUp power)
{
	int mult;
	if (start) mult = 1;
	else	   mult = -1;


	switch (power.get_powerType())
	{
	case ballSpeedUp:
		speed += mult * PowerUp::BALL_SPEED_CHANGE;
		break;
	case ballSpeedDown:
		speed -= mult * PowerUp::BALL_SPEED_CHANGE;
		break;
	default:
		break;
	}
	update_moveVect();
}