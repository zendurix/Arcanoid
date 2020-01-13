#include "GAME.h"


GAME::GAME() 
{
	windowPtr = nullptr;
	displayText = MENU::init_text();
	displayText.setFillColor(sf::Color::Yellow);
	displayText.setCharacterSize(20);
	displayText.setPosition(WINDOW_LENGTH - WINDOW_RIGHT_BORDER + 20, 10);
}

GAME::~GAME()
{
}


void GAME::init_entities()
{
	make_platform();
	make_boundaries();
	make_blocks();
	make_ball(platform->get_posX() + 40, platform->get_posY() - 20, 43);
}

void GAME::reset_game()
{
	entities.clear();
	powerUpsEntities.clear();
	entitiesTrashCan.clear();
	balls.clear();
	playerHP = PLAYER_START_HP;
	points = 0;
	init_entities();
}

void GAME::set_windowPtr(sf::RenderWindow* window)
{
	if (windowPtr == nullptr)
	{
		windowPtr = window;
	}
}























void GAME::make_platform()
{
	platform = std::make_shared <Platform>();
	entities.push_back(platform);
}

void GAME::make_ball(int x, int y, double angle)
{
	std::shared_ptr newBall = std::make_shared <Ball>(x, y, angle);
	entities.push_front(newBall);
	balls.push_back(newBall);
}

void GAME::make_boundaries(bool addWallDown)
{
	std::shared_ptr<Wall> wallLeft  = std::make_shared<Wall>(WALL_THICK, WINDOW_HEIGHT, 0, 0);
	std::shared_ptr<Wall> wallRight = std::make_shared<Wall>(WALL_THICK, WINDOW_HEIGHT, WINDOW_LENGTH- WINDOW_RIGHT_BORDER- WALL_THICK, 0);
	std::shared_ptr<Wall> wallUp    = std::make_shared<Wall>(WINDOW_LENGTH - WINDOW_RIGHT_BORDER, WALL_THICK, 1, 0);
	entities.push_back(wallLeft);
	entities.push_back(wallRight);
	entities.push_back(wallUp);
	if (addWallDown) 
	{
		std::shared_ptr<Wall> wallDown = std::make_shared<Wall>(WINDOW_LENGTH - WINDOW_RIGHT_BORDER, WALL_THICK, 0, WINDOW_HEIGHT - WALL_THICK);
		entities.push_back(wallDown);
	}
}

void GAME::make_blocks()
{
	int blocksCol = (WINDOW_HEIGHT - 400) / (BLOCK_SIZE / 2);  
	int blocksRow = (WINDOW_LENGTH - (WINDOW_RIGHT_BORDER + 30)) / (BLOCK_SIZE + SPACE_BETWEEN_BLOCKS + 5);
	blocksCount = blocksCol * (blocksRow-2);
	int startX = ((WINDOW_LENGTH - WINDOW_RIGHT_BORDER) + WALL_THICK) / (blocksRow + SPACE_BETWEEN_BLOCKS);
	int startY = 30;
	int hp = 1;

	for (int i = 0; i < blocksCol; i++)
	{
		if (i == blocksCol - 1)
			hp = 2;
		for (int j = 0; j < blocksRow; j++)
		{
			if (j != blocksRow / 2 && j != blocksRow / 2 - 1)
				entities.push_back(std::make_shared<Block>(hp, startX + j * (BLOCK_SIZE + SPACE_BETWEEN_BLOCKS), startY + i * (BLOCK_SIZE/2 + 0)));
		}
	}
}

void GAME::make_powerUp(std::shared_ptr<Entity> blockFrom)
{
	int rand = random(0, 100);
	if (rand <= PowerUp::DROP_CHANCE_PERCENT)
	{
		sf::Vector2f pos = blockFrom->get_shape()->getPosition();
		ePowerType power = random_from_vect(PowerUp::POWERS_ALL);
		std::shared_ptr <PowerUp> powerUp = std::make_shared<PowerUp>(power, &tickCounter, pos.x + 20, pos.y);
		entities.push_front(powerUp);
		powerUpsEntities.push_back(powerUp);
	}
}

void GAME::make_2_bullets()
{
	float leftX = platform->get_posX() + 5;
	float rightX = leftX + platform->get_length() - 10;
	float y = platform->get_posY() - 6;
	entities.push_back(std::make_shared<Bullet>(leftX, y));
	entities.push_back(std::make_shared<Bullet>(rightX, y));
}


void GAME::test_ball_colllisions()
{
	make_boundaries(true);
	playerHP = PLAYER_START_HP;
	make_platform();
	int angle;

	for (int i = 1; i < 10; i++)
	{
		angle = random(1, 359);
		make_ball(i * 20, i * 20, angle);
		make_ball(i * 20, i * 20, angle+100);
		make_ball(i * 20, i * 20, angle+200);
		make_ball(i * 20, i * 20, angle + 300);
		make_ball(i * 20, i * 20, angle + 400);
	}
}




































void GAME::destroy_entity(std::shared_ptr<Entity> entity)
{
	switch (entity->get_entityType())
	{
	case powerUpEnt:
		{
		auto position1 = std::find(powerUpsEntities.begin(), powerUpsEntities.end(), entity);
		powerUpsEntities.erase(position1);
		}
		break;

	case circleEnt:
		{
		auto position2 = std::find(balls.begin(), balls.end(), entity);
		balls.erase(position2);
		}
		break;
	}
	auto position = std::find(entities.begin(), entities.end(), entity);
	entities.erase(position);
}

void GAME::move_to_trashCan_unActives()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->get_active())
			entitiesTrashCan.push_back(entities[i]);
	}
}

void GAME::clear_entitiesTrashCan()
{
	while (entitiesTrashCan.size() != 0)
	{
		destroy_entity(entitiesTrashCan.front());
		entitiesTrashCan.erase(entitiesTrashCan.begin());
	}
	entitiesTrashCan.clear();
}


























void GAME::tick()
{

	move_entities();
	collide_entities();
	move_to_trashCan_unActives();
	clear_entitiesTrashCan();

	if (balls.size() == 0)
	{
		playerHP--;
		if (playerHP > 0)
		{
			float angle;
			do
			{
				angle = random(25, 335);
			} while ((angle > 50 && angle < 310));
			make_ball(platform->get_posX() + 50, platform->get_posY() - 50, angle);
		}
	}
	if (balls.size() == 1)
	{ // fix angle if too vertical or too horizontal
		float angle = balls[0]->get_circleMoveAngle();
		if (angle < 5 || angle > 355)
			angle = 40;
		else if (angle > 85 && angle < 95)
			angle = 300;
		else if (angle > 265 && angle < 275)
			angle = 40;
		balls[0]->set_circleMoveAngle(angle);
	}
}









































void GAME::display_update()
{
	windowPtr->clear();
	for (std::shared_ptr<Entity> entity : entities)
	{
		if (entity->get_active())
		{
			windowPtr->draw(*entity->get_shape());
		}
	}

	if (DEBUG) // TEST shows ball dir
	{
		for (std::shared_ptr<Ball> ball: balls)
		{
			sf::Vector2f ballCenter(ball->get_circleShape()->getPosition().x + ball->get_circleShape()->getRadius(),
				ball->get_circleShape()->getPosition().y + ball->get_circleShape()->getRadius());
			sf::Vector2f ballDir(ballCenter.x + 30 * ball->get_moveVect().x,
				ballCenter.y + 30 * ball->get_moveVect().y);

			sf::Vertex line[] =	{ballCenter, ballDir};
			windowPtr->draw(line, 2, sf::Lines);
		}
	}

	update_displayText();
	windowPtr->draw(displayText);

	windowPtr->display();
}

void GAME::update_displayText()
{
	stringSetter = "\n   FPS:    " + std::to_string(fpsCount)		+ 
				   "\n   POINTS: " + std::to_string(points)			+
				   "\n   HEALTH: " + std::to_string(playerHP)		+ 
				   "\n   BALLS:  " + std::to_string(balls.size())	+
				   "\n\n BALL ANGLE: "   + std::to_string((int)balls.at(0)->get_circleMoveAngle()) +
				   "\n BALL SPEED: "     + std::to_string((int)(balls.at(0)->get_speed()*100.0)) +
				   "\n\n PLATF LENGTH: " + std::to_string((int)platform->get_length()) +
				   "\n PLATF SPEED:  "   + std::to_string((int)(platform->get_speed()*100.0)) +
			   "\n\n\nPOWERS: TIME LEFT:" 	;
	std::vector< std::pair<std::string, int> > powersToDisplay;
	std::pair<std::string, int> powerPair;
	for (PowerUp power : platform->get_activePowerUps())
	{		
		switch (power.get_powerType())
		{
		case guns:			 powerPair.first = "guns          ";	 break; 
		case platformBig:	 powerPair.first = "platformBig   ";	 break; 
		case platformSmall:	 powerPair.first = "platformSmall ";	 break; 
		case platfSpeedUp:	 powerPair.first = "platfSpeedUp  ";	 break; 
		case platfSpeedDown: powerPair.first = "platfSpeedDown";	 break; 
		}
		powerPair.second = power.timeLeft(); 
		powersToDisplay.push_back(powerPair);
	}
	for (PowerUp power : *Ball::get_ballsActivePowerUpsPtr())
	{
		switch (power.get_powerType())
		{
		case ballSpeedUp:	powerPair.first = "ballSpeedUp   ";	     break;  
		case ballSpeedDown:	powerPair.first = "ballSpeedDown ";	     break;  
		}
		powerPair.second = power.timeLeft();  
		powersToDisplay.push_back(powerPair);
	}

	std::sort(powersToDisplay.begin(), powersToDisplay.end(), 
		[](auto &left, auto &right) {return left.second > right.second;	});
	
	for (auto display : powersToDisplay)
	{
		stringSetter += "\n" + display.first + " " + std::to_string(display.second);
	}
	displayText.setString(stringSetter);
}










































void GAME::control_platform(eDirections inp)
{
	platform->update_moveVect(inp);
}


void GAME::move_entities()
{
	std::shared_ptr<Entity> collided;

	for (int i = 0; i < entities.size(); i++)
	{
		std::shared_ptr <Entity> entity = entities[i];
		if (entity->get_movable())
		{
			entity->update_prevXY();
			entity->move();
		}
		if (entity->get_entityType() == circleEnt   || 
			entity->get_entityType() == platformEnt || 
			entity->get_entityType() == bulletEnt)
		{
			collided = check_collisions(entity);	
			if (collided != nullptr)
			{	
				eCollision collissionType = entity->get_collided();
				Collision collision(entity, collided, collissionType);
				if (std::find(collisions.begin(), collisions.end(), Collision(collided, entity, collissionType)) == collisions.end())
				{// check for collision duplicate
					collisions.push_back(collision);
				}
			}
		}
	}
}




























std::shared_ptr<Entity> GAME::check_collisions(std::shared_ptr<Entity> entity)
{
	for (int i = 0; i < entities.size(); i++)
	{
		std::shared_ptr <Entity> ent = entities[i];
		if (ent == entity )
			continue; // don't check collision with itself
		else
		{
			eEntityType entityType = entity->get_entityType();
			eEntityType entType    = ent->get_entityType();

			std::shared_ptr<sf::CircleShape>    circle1 = entity->get_circleShape();
			std::shared_ptr<sf::RectangleShape> rect1 = entity->get_rectShape();
			std::shared_ptr<sf::CircleShape>    circle2 = ent->get_circleShape();
			std::shared_ptr<sf::RectangleShape> rect2 = ent->get_rectShape();

			if (entityType == circleEnt)
			{
				if (entType == circleEnt)
				{
					entity->set_collided(Physics::collision(*circle1, *circle2));
					if (entity->get_collided() != noCollision)
						return ent;
				}
				else if (entType == wallEnt || entType == platformEnt || entType == blockEnt)
				{
					entity->set_collided(Physics::collision(*rect2, *circle1));
					if (entity->get_collided() != noCollision)
						return ent;
				}
			}
			else if (entityType == platformEnt)
			{
				if (entType == circleEnt)
				{
					entity->set_collided(Physics::collision(*rect1, *circle2));
					if (entity->get_collided() != noCollision)
						return ent;
				}
				else if (entType == wallEnt || entType == platformEnt || entType == powerUpEnt)
				{
					entity->set_collided(Physics::collision(*rect1, *rect2));
					if (entity->get_collided() != noCollision)
						return ent;
				}
			}
			else if (entityType == bulletEnt)
			{
				if (entType == blockEnt)
				{
					entity->set_collided(Physics::collision(*rect1, *rect2));
					if (entity->get_collided() != noCollision)
						return ent;
					else
						entity->set_collided(noCollision);

				}
				else
					entity->set_collided(noCollision);
			}
			else 
			{
				continue;
			}
		}
	}
	return nullptr;
}


















void GAME::collide_entities()
{
	for (Collision collision : collisions)
	{
		std::shared_ptr<Entity> entity   = std::get<0>(collision);
		std::shared_ptr<Entity> collided = std::get<1>(collision);
		eCollision collisionType         = std::get<2>(collision);
		
		if (entity->get_entityType() == circleEnt)
		{	
			if (collided->get_entityType() == circleEnt)
			{
				if (Physics::collision(*entity->get_circleShape(), *collided->get_circleShape()) != noCollision) // check if still colliding
				{
					double anglePrev1 = entity->get_circleMoveAngle();
					double anglePrev2 = collided->get_circleMoveAngle();
										
					sf::Vector2f ball1(entity->get_posX(), entity->get_posY());
					sf::Vector2f ball2(collided->get_posX(), collided->get_posY());

					// Distance between ball centers
					float distance = Physics::distance_meter(ball1, ball2);

					// Calculate displacement required
					float overlap = 0.5f * (distance - entity->get_circleShape()->getRadius() - collided->get_circleShape()->getRadius());

					// Displace balls away from collision
					entity->get_shape()->setPosition(ball1.x - overlap * (ball1.x - ball2.x) / distance,
													 ball1.y - overlap * (ball1.y - ball2.y) / distance);
					collided->get_shape()->setPosition(ball2.x + overlap * (ball1.x - ball2.x) / distance,
													   ball2.y + overlap * (ball1.y - ball2.y) / distance);
					entity->update_prevXY();
					collided->update_prevXY();

					sf::Vector2f vect1 = entity->get_moveVect();
					sf::Vector2f vect2 = collided->get_moveVect();

					sf::Vector2f vect1Copy = vect1;
					sf::Vector2f vect2Copy = vect2;									   

					Physics::rebound_angle(*entity->get_circleShape(), *collided->get_circleShape(), vect1, vect2);

					entity->set_moveVect(vect1);
					collided->set_moveVect(vect2);

					entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
					collided->get_shape()->setPosition(collided->get_prevX(), collided->get_prevY());
					
					double angle1 = Physics::angle_vect_axisY(vect1);
					double angle2 = Physics::angle_vect_axisY(vect2);
					
					entity->move();
					collided->move();
					if (abs(angle1 - angle2) <= 0.5 || 
						(Physics::collision(*entity->get_circleShape(), *collided->get_circleShape()) == pointCollision))
					{ // make sure that balls aren't still colliding after moving. if so change a little bit there angles
						angle1 -= 25.0;
						angle2 += 25.0;

						angle1 = Physics::check_angle_in_360(angle1);
						angle2 = Physics::check_angle_in_360(angle2);

						entity->set_circleMoveAngle(angle1);
						collided->set_circleMoveAngle(angle2);

						entity->update_moveVect();
						collided->update_moveVect();

						entity->move();
						collided->move();
					}
					if (Physics::collision(*entity->get_circleShape(), *collided->get_circleShape()) == pointCollision)
					{// change angles in oposite dir if still colliding
						angle1 += 50.0;
						angle2 -= 50.0;

						angle1 = Physics::check_angle_in_360(angle1);
						angle2 = Physics::check_angle_in_360(angle2);

						entity->set_circleMoveAngle(angle1);
						collided->set_circleMoveAngle(angle2);

						entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
						collided->get_shape()->setPosition(collided->get_prevX(), collided->get_prevY());

						entity->update_moveVect();
						collided->update_moveVect();

						entity->move();
						collided->move();
					}
					if (Physics::collision(*entity->get_circleShape(), *collided->get_circleShape()) == pointCollision)
					{ // still colliding - swap angles;
						angle1 = anglePrev2;
						angle2 = anglePrev1;
					}

					entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
					collided->get_shape()->setPosition(collided->get_prevX(), collided->get_prevY());

					LOG("BALLS BOUNCE   " << angle1 << "    " << angle2);

					entity->set_circleMoveAngle(angle1);
					collided->set_circleMoveAngle(angle2);
				}
			}
					   
			else if (collisionType == lineCollision)
			{
				entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
				double angle = Physics::rebound_angle(*collided->get_rectShape(), *entity->get_circleShape(), entity->get_circleMoveAngle());
				entity->set_circleMoveAngle(angle);

				// check for ball on wall overlaps
				if (Physics::collision(*collided->get_rectShape(), *entity->get_circleShape()) != noCollision)
				{
					if (collided->get_posX() == 0 && collided->get_posY() == 0)
					{ // wallLeft
						entity->get_shape()->setPosition(entity->get_prevX() + WALL_THICK, entity->get_prevY());
					}
					else if (collided->get_posX() == WINDOW_LENGTH - WINDOW_RIGHT_BORDER - 12 && collided->get_posY() == 0)
					{ // wallRight
						entity->get_shape()->setPosition(entity->get_prevX() - WALL_THICK, entity->get_prevY());
					}
					else if (collided->get_posX() == 1 && collided->get_posY() == 0)
					{ // wallUp
						entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY() + WALL_THICK);
					}
					else if (collided->get_posX() == 0 && collided->get_posY() == WINDOW_HEIGHT - 12)
					{ // wallDown
						entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY() - WALL_THICK);
					}
				}

			}
			/* // DELETED
			else if (collisionType == pointCollision) 
			{
				entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
				
				entity->set_circleMoveAngle(Physics::rebound_angle(*collided->get_rectShape(), *entity->get_circleShape(), entity->get_circleMoveAngle()));
				entity->update_moveVect();

				entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
				if (collided->get_entityType() == platformEnt)
				{
					entity->update_moveVect();
					while (entity->get_posY() + 2 * entity->get_circleShape()->getRadius() >= collided->get_posY())     //((Physics::collision(*collided->get_rectShape(), *entity->get_circleShape()) != noCollision))
					{// move away from platf corner to avoid overlaping
						entity->move(); 
					}
				}
			}
			*/
			if (collided->get_entityType() == blockEnt)
			{
				collided->hit();
				if (!collided->get_active())
				{
					blocksCount--;
					make_powerUp(collided);
				}
				points++;
			}
			if (collided->get_entityType() == platformEnt)
			{
				int y = entity->get_prevY();
				while (entity->get_posY() + entity->get_circleShape()->getRadius()*2 > collided->get_posY())
				{ // move ball away from platform to avoid platform overlaping ball
					y--;
					entity->get_shape()->setPosition(entity->get_prevX(), y);
				}
			}

			entity->update_moveVect();
			collided->update_moveVect();
		}
		else if (entity->get_entityType() == platformEnt)
		{
			if (collided->get_entityType() == wallEnt)
				entity->get_shape()->setPosition(entity->get_prevX(), entity->get_prevY());
			else if (collided->get_entityType() == powerUpEnt)
			{
				collided_powerUp(collided);
			}
		}
		else if (entity->get_entityType() == bulletEnt)
		{
			if (collided->get_entityType() == blockEnt)
			{
				collided->hit();
				if (!collided->get_active())
				{
					blocksCount--;
					make_powerUp(collided);
				}
				points++;
				entity->set_active(false);
			}
		}
	}
	collisions.clear();
}















































void GAME::collided_powerUp(std::shared_ptr<Entity> collided)
{
	auto iterator = std::find(powerUpsEntities.begin(), powerUpsEntities.end(), collided);
	int position = std::distance(powerUpsEntities.begin(), iterator);
	PowerUp power = *powerUpsEntities.at(position);
	switch (power.get_powerType())
	{
	case ballSpeedUp:
	case ballSpeedDown:
	{
		bool check = false;
		for (auto ball : balls)
		{
			if (ball->get_speed() > PowerUp::BALL_SPEED_CHANGE + 0.15f)
			{
				ball->pick_powerup(power);
				check = true;
			}
		}
		if (check)
		{
			Ball::get_ballsActivePowerUpsPtr()->push_back(power);
		}
	}
		break;

	case ballx3:
	{
		int x = balls[balls.size()-1]->get_shape()->getPosition().x;
		int y = balls[balls.size()-1]->get_shape()->getPosition().y;
		make_ball(platform->get_shape()->getPosition().x, platform->get_shape()->getPosition().y - 30 , 315);
		make_ball(platform->get_shape()->getPosition().x + 50, platform->get_shape()->getPosition().y - 30 , 45);
	}
		break;
	case guns:
		if (!platform->get_haveGuns())
			platform->pick_powerup(power);
		break;
	case platformSmall:
		if (platform->get_length() > 100)
			platform->pick_powerup(power);
		break;
	case platformBig:
		if (platform->get_length() < WINDOW_LENGTH - 2 * WINDOW_RIGHT_BORDER)
			platform->pick_powerup(power);
		break;
	case platfSpeedDown:
		if (platform->get_speed() > PowerUp::PLATFORM_SPEED_CHANGE + 0.2f)
			platform->pick_powerup(power);
		break;		
	default: // rest powers for platform
		platform->pick_powerup(power);
		break;
	}

	if (power.get_goodPower())
		points += 3;
	else
		points -= 3;

	entitiesTrashCan.push_back(collided);
}


void GAME::balls_check_powerUps_duration()
{
	for (auto ball : balls)
		ball->check_powerUps_duration();
	std::vector<PowerUp>* vec = Ball::get_ballsActivePowerUpsPtr();

	for (PowerUp& power : *vec)
	{
		power.incr_timeAlive();
		if (!power.get_active())
			vec->erase(std::find(vec->begin(), vec->end(), power));
	}
}

void GAME::check_powerUps_duration()
{
	get_platform()->check_powerUps_duration();
	balls_check_powerUps_duration();

	if (platform->get_haveGuns())
		if (tickCounter % BULLETS_WAIT == 0)
			make_2_bullets();
}