/*
 * whirlpool.cpp
 *
 *  Created on: May 3, 2009
 *      Author: urioxis
 */

#include "whirlpool.hpp"

Whirlpool::Whirlpool(int x, int y)	{
	id = -1;
	this->cell = -1;
	direction = 0;
	type = POOL;
	location.x = x;
	location.y = y;
	score = 0;
	hwidth = 50;
	hheight = 50;
	bbox.hheight = 25;
	bbox.hwidth = 25;
	bbox.c = &this->location;
	pool = glGenLists(1);
	glNewList(pool, GL_COMPILE);
		glPushMatrix();
		glBegin(GL_POLYGON);
			glColor3f(0.0,0.1,0.3);
			glVertex2f(0, 0);
			for(int i=0; i<=360; i+=5)	{
				if((i >= 40 && i <= 50) || (i >= 85 && i <= 95) || (i >= 130 && i <= 140) || (i >= 175 && i <= 185) || (i >= 220 && i <= 230) || (i >= 265 && i <= 275) || (i >= 310 && i <= 320) || i >= 355 || i <= 5)	{
					glColor3f(0.0,0.1,0.3);
				}
				else	{
					glColor3f(0.0,0.2,0.9);
				}
				float xcoord = 0 + 1024/20 * cos(D2R(i));
				float ycoord = 0 + 1024/20 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glPopMatrix();
	glEndList();
}

Whirlpool::~Whirlpool()	{

}

void Whirlpool::attack(bool t)	{
}

Collision Whirlpool::collide(Actor* a)	{
	Collision c;
	return c;
}

void Whirlpool::die()	{
}

Collision Whirlpool::detectCollisions()	{
	Collision c;
	return c;
}
