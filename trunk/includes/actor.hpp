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
	virtual void collide(Actor*) = 0;
	float getDirection()	{
		return direction;
	}
	Coordinate getLocation()	{
		return location;
	}
	void setCurrentCell(int c)	{
		this->cell = c;
	}

protected:
	virtual void detectCollisions() = 0;
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

private:
};
#endif //__ACTOR_HPP__
