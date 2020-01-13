#pragma once

#include <cmath>

#include "SFML/Graphics.hpp"

#include "CONFIGURATION.h"


const double PI = 3.14159265359;

class Physics
{
private:
	Physics() = delete;
public:

	static double check_angle_in_360(double angle);

	static double dot_product(sf::Vector2f vectA, sf::Vector2f vectB);

	static double distance_meter(int x1, int y1, int x2, int y2);
	static double distance_meter(sf::Vector2f p1, sf::Vector2f p2);

	static bool are_same_double(double a, double b);

	static double distance_line_to_point(sf::Vector2f lineA, sf::Vector2f lineB, sf::Vector2f point);

	static sf::Vector2f closest_point_from_points(sf::Vector2f point, std::vector<sf::Vector2f> points);

	static sf::Vector2f second_point_from_closest_side(std::vector<sf::Vector2f> vertexes, sf::Vector2f closestPoint, sf::Vector2f point);
	
	static eCollision collision(sf::RectangleShape rect1, sf::RectangleShape rect2);
	static eCollision collision(sf::RectangleShape rect, sf::CircleShape circle);
	static eCollision collision(sf::CircleShape circle1, sf::CircleShape circle2);

	static char check_angle_quarter(double angle);
	static char check_angle_quarter(sf::Vector2f vector);

	static double degree_to_radian(double deg);
	static double radian_to_degree(double rad);

	static double rebound_angle(sf::RectangleShape rect, sf::CircleShape circle, double angle);
	//static double rebound_angle(double angle); //DELETED
	static void   rebound_angle(sf::CircleShape circle1, sf::CircleShape circle2, sf::Vector2f& moveVect1, sf::Vector2f& moveVect2r);

	static eDirections position_circle_to_rect(sf::CircleShape circle, sf::RectangleShape rect);
	static std::vector <sf::Vector2f> make_vertex_vector(sf::RectangleShape rect);

	static double angle_vect_axisY(sf::Vector2f vector);

	static double magnitude(sf::Vector2f vector);

	   
	template <typename T>
	static void swap_values(T& val1, T& val2)
	{
		val1 = val1 + val2;
		val2 = val1 - val2;
		val1 = val1 - val2;
	}


};

