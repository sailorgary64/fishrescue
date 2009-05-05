/*
 * whirlpool.hpp
 *
 *  Created on: May 3, 2009
 *      Author: urioxis
 */

#ifndef WHIRLPOOL_HPP_
#define WHIRLPOOL_HPP_

#include "includes.hpp"
#include "actor.hpp"

class Whirlpool : public Actor	{
public:
	Whirlpool(int x, int y);
	~Whirlpool();
	void draw(Coordinate);
	void attack(bool);
	Collision collide(Actor*);
	void die();
	Collision detectCollisions();

private:
	GLuint pool;
};

inline void Whirlpool::draw(Coordinate playerLoc)	{
	glPushMatrix();
	glTranslatef(location.x - playerLoc.x, location.y - playerLoc.y, 0);
	glRotatef(direction, 0.0, 0.0, 1.0);
	glCallList(pool);
	direction += 3.0f;
	if(direction >= 360)	{
		direction -= 360;
	}
	glPopMatrix();
}

#endif /* WHIRLPOOL_HPP_ */
