/*
 * friendly.hpp
 *
 *  Created on: Apr 8, 2009
 *      Author: urioxis
 */

#ifndef __FRIENDLY_HPP__
#define __FRIENDLY_HPP__

#include "includes.hpp"
#include "actor.hpp"
#include "player.hpp"

class Friendly: public Actor {
public:
	Friendly(int);
	virtual ~Friendly();
	void draw();
	void attack(bool);
	Collision collide(Actor*);
	void die();

private:
	Collision detectCollisions();
	//static Coordinate location;
	//Vector velocity;
	Collision collision;
	float acceleration;
	float deceleration;
	float dirToPlayer;
	float dtheta;
	float dX;
	float dY;
	bool following;
	float calculatePlayerDirection();
	bool playerNearby();
	bool enemyNearby();
	GLuint friends;
	Actor* closestEnemy;
	Actor* playerHandle;
};

inline void Friendly::draw()	{
	int currentFps = Fps::getFps();
	if (currentFps < 1)	{
		currentFps = 1;
	}
	if (playerNearby() && following)	{
		turnToActor(playerHandle);
	}
	else if (enemyNearby())	{
		turnFromActor(this->closestEnemy);
	}
	else	{
		this->forward(false);
		this->right(false);
		this->left(false);
	}

	//Turn the fish
	if (l)	{
		if (dTheta <= 0.8)	{
			dTheta += 0.01;
		}
	}
	else if (r)	{
		if (dTheta >= -0.8)	{
			dTheta -= 0.01;
		}
	}
	else {
		dTheta /= 1.1;
		if (dTheta < 0.3 && dTheta > -0.3)	{
			dTheta = 0;
		}
	}
	direction += dTheta;
	if (direction >= 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}

	//Move the fish
	if (f)	{
		dX = acceleration*cos(D2R(this->direction));
		dY = acceleration*sin(D2R(this->direction));
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else {
		velocity.vx *= ((1-deceleration));
		velocity.vy *= ((1-deceleration));
	}
	velocity.magnitude = sqrt(velocity.vx*velocity.vx + velocity.vy*velocity.vy);
	if(velocity.magnitude > 1.5)	{
		float tempDecel = (0.5/velocity.magnitude);
		velocity.vx *= tempDecel;
		velocity.vy *= tempDecel;
	}
	if(this->cell != -1)	{
		detectCollisions();
	}
	if(this->collision.happened)	{
		velocity.vx = collision.vx;
		velocity.vy = collision.vy;
	}

	location.x += velocity.vx;
	location.y += velocity.vy;

	//Final stuff
	glPushMatrix();
	glTranslatef(location.x,location.y,0);
	glRotatef((direction),0.0,0.0,1.0);
	glCallList(friends);
	glPopMatrix();
}

#endif /* __FRIENDLY_HPP__ */
