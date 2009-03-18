#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include "includes.hpp"
#include "fps.hpp"

//Abstract class
class Actor	{
public:
	Actor()	{
	};
	virtual ~Actor()	{
	};
	virtual void draw() = 0;	//Draws the actor
	virtual void left(bool) = 0;
	virtual void right(bool) = 0;
	virtual void forward(bool) = 0;
	virtual void backward(bool) = 0;
	virtual void attack(bool) = 0;
	float getDirection()	{
		return direction;
	}
	Coordinate getLocation()	{
		return location;
	}
	Vector getVelocity()	{
		return velocity;
	}
	float getDistance(Coordinate otherLoc)	{
		float diffx = abs(otherLoc.x - location.x);
		float diffy = abs(otherLoc.y - location.y);
		float dist = (float)sqrt((diffx*diffx)+(diffy*diffy));
		return dist - bbox.hwidth;
	}
	void setCurrentCell(int c)	{
		this->cell = c;
	}
	int getCurrentCellId()	{
		return this->cell;
	}
	int getId()	{
		return this->id;
	}
	virtual Collision collide(Actor*) = 0;
	virtual void die() = 0;
	bool attacking;

protected:
	int id;
	int lives;
	Coordinate location;	//contains the actor's location
	Vector velocity;
	float direction;
	bool l;
	bool r;
	bool f;
	bool b;
	float dTheta;
	float dX;
	float dY;
	float acceleration;
	static const float deceleration;
	AABB bbox;
	int cell;

	virtual Collision detectCollisions() = 0;

private:
};
#endif //__ACTOR_HPP__
