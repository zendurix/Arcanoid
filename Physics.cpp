#include "Physics.h"


double Physics::check_angle_in_360(double angle)
{
	while (angle > 360.0)
		angle -= 360.0;
	while (angle < 0)
		angle += 360.0;
	return angle;
}




double Physics::dot_product(sf::Vector2f vectA, sf::Vector2f vectB)
{
	return vectA.x * vectB.x + vectA.y * vectB.y;
}










double Physics::distance_meter(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double Physics::distance_meter(sf::Vector2f p1, sf::Vector2f p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

bool Physics::are_same_double(double a, double b)
{
	const double EPSILON = 0.0000001;
	return fabs(a - b) < EPSILON;
}










double Physics::distance_line_to_point(sf::Vector2f lineA, sf::Vector2f lineB, sf::Vector2f point)
{
	double x1 = lineA.x, y1 = lineA.y;
	double x2 = lineB.x, y2 = lineB.y;
	double xP = point.x, yP = point.y;
	if (are_same_double(x1,x2)) x2 -= 0.00000001; // to avoid dividing by 0
	return abs((y2 - y1) / (x2 - x1)*xP - yP + (x2*y1 - x1 * y2) / (x2 - x1)) / 
		   sqrt(pow((y2 - y1) / (x2 - x1), 2) + 1);
}











sf::Vector2f Physics::closest_point_from_points(sf::Vector2f point, std::vector<sf::Vector2f> points)
{
	std::vector <double> pointsDistances;
	sf::Vector2f closestPoint = points[0];
	double bestDist = 100000000.0;
	int bestDistId;
	double currentDist;

	for (sf::Vector2f x : points)
	{
		currentDist = distance_meter(point, x);
		pointsDistances.push_back(currentDist);
		if (currentDist < bestDist)
		{
			bestDist = currentDist;
			bestDistId = pointsDistances.size() - 1;
		}
	}
	return points[bestDistId];
}	











sf::Vector2f Physics::second_point_from_closest_side(std::vector<sf::Vector2f> vertexes,
													sf::Vector2f closestPoint, sf::Vector2f point)
{ 
	sf::Vector2f secondPoint;
	sf::Vector2f falseReturn(-1, -1);

	if (closestPoint == vertexes[0])
	{
		if (point.x < closestPoint.x)
		{
			if (point.y < vertexes[0].y)
				return falseReturn;
			secondPoint = vertexes[3];
		}
		else
			secondPoint = vertexes[1];
	}
	else if (closestPoint == vertexes[1])
	{
		if (point.x < closestPoint.x)
			secondPoint = vertexes[0];
		else
		{
			if (point.y < vertexes[1].y)
				return falseReturn;
			secondPoint = vertexes[2];
		}
	}
	else if (closestPoint == vertexes[2])
	{
		if (point.x < closestPoint.x)
		{
			if (point.x < vertexes[3].x)
				return falseReturn;
			secondPoint = vertexes[3];
		}
		else
		{
			if (point.y > vertexes[2].y)
				return falseReturn;
			secondPoint = vertexes[1];
		}
	}
	else if (closestPoint == vertexes[3])
	{
		if (point.x < closestPoint.x)
		{
			if (point.y > vertexes[3].y)
				return falseReturn;
			secondPoint = vertexes[0];
		}
		else
			secondPoint = vertexes[2];
	}
	return secondPoint;
}











eCollision Physics::collision(sf::RectangleShape rect1, sf::RectangleShape rect2)
{
	if (rect1.getGlobalBounds().intersects(rect2.getGlobalBounds()))
		return lineCollision;
	else 
		return noCollision;
}
eCollision Physics::collision(sf::RectangleShape rect, sf::CircleShape circle)
{
	if (rect.getGlobalBounds().intersects(circle.getGlobalBounds())) // they might be colliding
	{
		return lineCollision;
/* FOR DISTINGUISHING CORNER FROM SIDE COLLISION ( NOT IMPLEMENTED PROPERLY, SO SIMPLIFIED VER IS USED)
		double radius = circle.getRadius();
		sf::Vector2f circleCenter(circle.getPosition().x + radius, circle.getPosition().y + radius);
		std::vector <sf::Vector2f> vertexes = make_vertex_vector(rect);
		sf::Vector2f closestPoint = closest_point_from_points(circleCenter, vertexes);

		if (distance_meter(closestPoint, circleCenter) - radius < 0.0001)
		{// check if collide with closest vertex
			return pointCollision;
			//corner collision are simplified!
		}

		sf::Vector2f circleEdgePoint;
		sf::Vector2f secondPoint = second_point_from_closest_side(vertexes, closestPoint, circleCenter);
		if (secondPoint == sf::Vector2f(-1, -1))
			return noCollision;
		int distance = distance_line_to_point(closestPoint, secondPoint, circleCenter);
		if (distance - radius < 0.0001)
		{// check if collide with closest side of rectangle
			return lineCollision;
		}
*/
	}
	return noCollision;
}
eCollision Physics::collision(sf::CircleShape circle1, sf::CircleShape circle2)
{
	sf::Vector2f center1(circle1.getPosition().x + circle1.getRadius(),
					 	 circle1.getPosition().y + circle1.getRadius());
	sf::Vector2f center2(circle2.getPosition().x + circle2.getRadius(),
						 circle2.getPosition().y + circle2.getRadius());
	double radiusesSum = circle1.getRadius() + circle2.getRadius();
	double centersDist = distance_meter(center1, center2);
			
	if (centersDist > radiusesSum)
		return noCollision;
	else // (centersDist <= radiusesSum)
		return pointCollision;  
}












char Physics::check_angle_quarter(double angle)
{
	if (angle >= 0.0  && angle <= 90.0)		return 1;
	if (angle > 90.0  && angle <= 180.0)	return 2;
	if (angle > 180.0 && angle <= 270.0)	return 3;
	if (angle > 270.0 && angle < 360.0)		return 4;
}
char Physics::check_angle_quarter(sf::Vector2f vect)
{
	if (vect.x >= 0 && vect.y <= 0)		return 1;
	if (vect.x >= 0 && vect.y >= 0)		return 2;
	if (vect.x <= 0 && vect.y >= 0)		return 3;
	if (vect.x <= 0 && vect.y <= 0)		return 4;
}












double Physics::degree_to_radian(double deg)
{
	return deg * PI / 180.0;
}
double Physics::radian_to_degree(double rad)
{
	return rad * 57.295779513;
}












double Physics::rebound_angle(sf::RectangleShape rect, sf::CircleShape circle, double angle)
{ // rebound from side of rectangle
	double rectX   = rect.getPosition().x;
	double rectY   = rect.getPosition().y;
	double circleX = circle.getPosition().x;
	double circleY = circle.getPosition().y;

	enum errorType { error = -1000 };

	double prevAngle = angle;
	eDirections position = position_circle_to_rect(circle, rect);
	LOG("prev angle: " << angle);

	if (angle == 0.0 || angle == 90.0 || angle == 180.0 || angle == 270.0 || angle == 360.0)
	{
		angle += 180.0;
	}
	else
	{
		switch (position)							
		{
		case up:
			LOG("pos: 1");
			if		(angle < 180.0 && angle >  90.0)	 angle = 180.0 - angle;
			else if (angle < 270.0 && angle > 180.0)	 angle = 540.0 - angle;
			else	angle  = error; // EROOR
			break;	
		case left:			
			LOG("pos: 2");
			if		(angle < 180.0 && angle > 90.0)	 angle = 360.0 - angle;
			else if (angle < 90.0 && angle  >  0.0)	 angle = 360.0 - angle;
			else	angle  = error; // EROOR
			break;	
		case down:	
			LOG("pos: 3");
			if		(angle < 90.0 && angle  >   0.0)	 angle = 180.0 - angle;
			else if (angle < 360.0 && angle > 270.0)	 angle = 540.0 - angle;
			else	angle  = error; // EROOR
			break;	
		case right:	
			LOG("pos: 4");
			if		(angle < 360.0 && angle > 270.0)	 angle = 360.0 - angle;
			else if (angle < 270.0 && angle > 180.0)	 angle = 360.0 - angle;
			else	angle  = error; // EROOR
			break;
		}
	}

	if (angle == error)
	{
		LOG("REBOUND ERR");
		angle = prevAngle;
	}

	angle = check_angle_in_360(angle);
	LOG("aft angle: " << angle);
	return angle;
}
/*double Physics::rebound_angle(double angle)  // DELETED
{ // rebound from point  
	////////////////////////////////  SIMPLIFIED METHOD
	if (angle < 10 || angle > 360)
		angle = 40;
	else if (angle > 80 && angle < 100)
		angle = 300;
	else if (angle > 260 && angle < 280)
		angle = 40;
	else
	{
		angle += 180.0;
		angle = check_angle_in_360(angle);
	}
	return angle;
	////////////////////////////////
}
*/
void Physics::rebound_angle(sf::CircleShape circle1, sf::CircleShape circle2, sf::Vector2f& moveVect1, sf::Vector2f& moveVect2)
{
	float radius1 = circle1.getRadius(),
		  radius2 = circle2.getRadius();
	sf::Vector2f center1(circle1.getPosition().x + radius1, circle1.getPosition().y + radius1);
	sf::Vector2f center2(circle2.getPosition().x + radius2, circle2.getPosition().y + radius2);
	
	moveVect1.y *= -1; // because in sfml (0, 0) is in upper corner, and vect for going up is (vect.y < 0) ...
	moveVect2.y *= -1; // ... where in real Coordinate system vect for going up is (vect.y > 0)

	// distance between circles
	float distance = distance_meter(center1, center2);

	// normal (distance vector)
	sf::Vector2f normal ((center2.x - center1.x) / distance, (center2.y - center1.y) / distance);
	
	// tangent (line tangental to normal)
	sf::Vector2f tangent (-normal.y, normal.x);

	// tangent dot product
	float dpTan1 = dot_product(moveVect1, tangent);
	float dpTan2 = dot_product(moveVect2, tangent);

	// normal dot product
	float dpNorm1 = dot_product(moveVect1, normal);
	float dpNorm2 = dot_product(moveVect2, normal);

	// Conservation of momentum in 1D
	float m1 = ( 2.0f * (radius1 * 10.0f) * dpNorm2) / (radius1 * 20.0f);
	float m2 = ( 2.0f * (radius1 * 10.0f) * dpNorm1) / (radius1 * 20.0f);

	// Update ball velocities
	moveVect1.x = tangent.x * dpTan1 + normal.x * m1;
	moveVect1.y = tangent.y * dpTan1 + normal.y * m1;
	moveVect2.x = tangent.x * dpTan2 + normal.x * m2;
	moveVect2.y = tangent.y * dpTan2 + normal.y * m2;

	moveVect1.y *= -1;
	moveVect2.y *= -1;
}












eDirections Physics::position_circle_to_rect(sf::CircleShape circle, sf::RectangleShape rect)
{
	std::vector <sf::Vector2f> vertexes = make_vertex_vector(rect);
	float circleX = circle.getPosition().x;
	float circleY = circle.getPosition().y;
	float centerX = circleX + circle.getRadius();
	float centerY = circleY + circle.getRadius();
	int radius = circle.getRadius();

	// SIMPLIFIED VERSION
	if (circleY + radius*2 <= vertexes[0].y)	return up;
	if (centerY - radius >= vertexes[3].y)		return down;
	if (centerX <= vertexes[0].x)				return left;
	if (centerX >= vertexes[1].x)				return right;



/*  FOR POINT COLLISIONS (NOT IMPLEMENTED)
	if (circleX > vertexes[0].x && circleX < vertexes[1].x)
	{
		if (circleY > vertexes[3].y)
			return down;
		else if (circleY < vertexes[0].y)
			return up;
	}
	else if (circleY > vertexes[0].y && circleY < vertexes[3].y)
	{
		if (circleX < vertexes[0].x)
			return left;
		else if (circleX >= vertexes[1].x)
			return right;
	}
	else if (circleX <= vertexes[0].x)
	{
		if (circleY <= vertexes[0].y)
			return upLeft;
		else if (circleY >= vertexes[3].y)
			return downLeft;
	}
	else if (circleX >= vertexes[1].x)
	{
		if (circleY <= vertexes[1].y)
			return upRight;
		else if (circleY >= vertexes[2].y)
			return downRight;
	}
*/
}











std::vector <sf::Vector2f> Physics::make_vertex_vector(sf::RectangleShape rect)
{
	/*
	*	A[0]------B[1]
	*	|			|
	*	D[3]------C[2]	
	*/
	return std::vector <sf::Vector2f>
	{
		/* A */sf::Vector2f(rect.getPosition().x,					 rect.getPosition().y),
		/* B */sf::Vector2f(rect.getPosition().x + rect.getSize().x, rect.getPosition().y),
		/* C */sf::Vector2f(rect.getPosition().x + rect.getSize().x, rect.getPosition().y + rect.getSize().y),
		/* D */sf::Vector2f(rect.getPosition().x,					 rect.getPosition().y + rect.getSize().y)
	};
}











double Physics::angle_vect_axisY(sf::Vector2f vector)
{ //angle between vect and vector (0, 1) 
	char quarter = Physics::check_angle_quarter(vector);
	double angle;

	switch (quarter)
	{
	case 1:						 vector.y *= (-1); 	break;
	case 2: vector.x *= (1);						break;
	case 3:	vector.x *= (-1);						break;
	case 4:	vector.x *= (-1);	 vector.y *= (-1);	break;
	}

	angle = atan(vector.y / vector.x);
	angle = radian_to_degree(angle);

	switch (quarter)
	{
	case 1:	angle = 90.0 - angle;	break;
	case 2:	angle = 90 + angle;	break;
	case 3:	angle = 270.0 - angle;	break;
	case 4:	angle = 270+ angle;	break;
	}

	return angle;
}











double Physics::magnitude(sf::Vector2f vector) // vector length
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}






/* DELETED


	float radius = circle.getRadius();
	sf::Vector2f center(circle.getPosition().x + radius, circle.getPosition().y + radius);

	moveVect.y *= -1; // because in sfml (0, 0) is in upper corner, and vect for going up is (vect.y < 0) ...
						 // ... where in real Coordinate system vect for going up is (vect.y > 0)

	// distance between circle and point
	float distance = distance_meter(center, point);

	// normal (distance vector)
	sf::Vector2f normal((point.x - center.x) / distance, (point.y - center.y) / distance);

	// tangent (line tangental to normal)
	sf::Vector2f tangent(-normal.y, normal.x);

	// tangent dot product
	float dpTan = dot_product(moveVect, tangent);

	// normal dot product
	float dpNorm = dot_product(moveVect, normal);


	float m1 = (2.0f * (radius * 10.0f) * dpNorm) / (radius * 20.0f);
	//float m2 = (2.0f * (radius1 * 10.0f) * dpNorm1) / (radius1 * 20.0f);

	// Update ball velocities
	moveVect.x = tangent.x * dpTan + normal.x * m1;
	moveVect.y = tangent.y * dpTan + normal.y * m1;

	//moveVect.y *= -1;

*/