#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <tuple>

#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"
#include "random_func.h"
#include "MENU.h"
#include "Entity.h"
#include "Platform.h"
#include "Ball.h"
#include "Wall.h"
#include "Block.h"
#include "PowerUp.h"
#include "Bullet.h"
#include "Physics.h"



class GAME
{
private:
	inline static GAME* instance = nullptr;
	GAME();

	sf::RenderWindow* windowPtr;

	std::deque  <std::shared_ptr<Entity>>  entities;
	std::vector <std::shared_ptr<PowerUp>> powerUpsEntities;
	std::vector <std::shared_ptr<Entity>>  entitiesTrashCan;
	std::vector <std::shared_ptr<Ball>>    balls;
	std::shared_ptr<Platform> platform;

	typedef std::tuple<std::shared_ptr<Entity>, std::shared_ptr<Entity>, eCollision> Collision;
	std::vector <Collision> collisions;

	std::string stringSetter;
	sf::Text displayText;
	int fpsCount;
	int tickCounter;

	int points;
	int blocksCount;
	int playerHP;

public:
	~GAME();
	static GAME* get_instance()
	{
		if (!instance)
		{
			instance = new GAME();
		}
		return instance;
	}

	void init_entities();
	void reset_game();
	   	 
	void make_platform();
	void make_ball(int x, int y, double angle);
	void make_boundaries(bool addWallDown = false);
	void make_blocks();
	void make_powerUp(std::shared_ptr<Entity> blockFrom);
	void make_2_bullets();
	void test_ball_colllisions();

	void destroy_entity(std::shared_ptr<Entity> entity);
	void move_to_trashCan_unActives();
	void clear_entitiesTrashCan();

	void tick();
	void display_update();
	void update_displayText();
	void control_platform(eDirections inp);
	void move_entities();

	std::shared_ptr<Entity> check_collisions(std::shared_ptr<Entity> entity);
	void collide_entities();
	void collided_powerUp(std::shared_ptr<Entity> collided);

	void balls_check_powerUps_duration();
	void check_powerUps_duration();

	int count_blocks() const { int i = 0; for (auto x : entities) if (x->get_entityType() == blockEnt)i++; return i; }

	// getters:
	int get_playerHP()							const { return playerHP; }
	std::shared_ptr<Platform> get_platform()	const { return platform; }
	int get_points()							const { return points; }
	int get_blocksCount()						const { return count_blocks(); }

	// setters:
	void set_windowPtr(sf::RenderWindow* window);
	void set_fpsCount(int fpsCounter) { fpsCount = fpsCounter; }
	void set_tickCounter(int set)	  { tickCounter = set; }
	void set_playerHp(int set)		  { playerHP = set; }
	void set_points(int set)		  { points = set; }

};