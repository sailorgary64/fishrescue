#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include "includes.hpp"

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
protected:
	int lives;
	Coordinate location;	//contains the actor's location
	Velocity velocity;
	float direction;
	bool l;
	bool r;
	bool f;
	bool b;
	float dTheta;
	float dX;
	float dY;
	float acceleration;
	float deceleration;
private:
};

#endif //__ACTOR_HPP__
