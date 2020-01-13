#pragma once

#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"



class Entity
{
protected:
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr <Entity> collidedWith;
	sf::Vector2f moveVect;
	eEntityType entityType;
	eCollision collided;

	float speed;
	float prevX, prevY;
	float circleMoveAngle;

	bool changedAngle;
	bool movable;
	bool active;
	
public:
	virtual ~Entity() = 0 {};

	void move()			 { shape->setPosition(shape->getPosition().x + moveVect.x, shape->getPosition().y + moveVect.y); }
	void update_prevXY() { prevX = get_posX(); prevY = get_posY(); }

	virtual bool get_active()	   { return true; }
	virtual void update_moveVect() { }
	virtual void hit()			   { }
	   
	// getters
	virtual std::shared_ptr<sf::RectangleShape>		get_rectShape() = 0;
	virtual std::shared_ptr<sf::CircleShape>		get_circleShape() = 0;

	std::shared_ptr <Entity> get_collidedWith()		const { return collidedWith; }
	std::shared_ptr<sf::Shape> get_shape()			const { return shape; }
	eEntityType get_entityType()					const { return entityType; }
	float get_prevX()								const { return prevX; }
	float get_prevY()								const { return prevY; }
	eCollision get_collided()						const { return collided; }
	double get_circleMoveAngle()					const { return circleMoveAngle; }
	bool get_movable()								const { return movable; }
	float get_speed()								const { return speed; }
	sf::Vector2f get_moveVect()						const { return moveVect; }
	float get_posX()								const { return shape->getPosition().x; }
	float get_posY()								const { return shape->getPosition().y; }

	// setters
	void set_prevY(float set)							{ prevY = set; }
	void set_prevX(float set)							{ prevX = set; }
	void set_speed(float set)							{ speed = set; }
	void set_collided(eCollision set)					{ collided = set; }
	void set_collidedWith(std::shared_ptr <Entity> set) { collidedWith = set; }
	void set_circleMoveAngle(double set)				{ circleMoveAngle = set; changedAngle = true; }
	void set_active(bool set)							{ active = set; }
	void set_moveVect(sf::Vector2f set)					{ moveVect = set; }
};

