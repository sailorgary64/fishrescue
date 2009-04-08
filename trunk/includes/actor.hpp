#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include "includes.hpp"
#include "fps.hpp"

typedef enum {PLAYER, ENEMY, FRIENDLY} actorType;

//Abstract class
class Actor	{
public:
	Actor()	{
	};
	virtual ~Actor()	{
	};
	virtual void draw() = 0;	//Draws the actor
	void left(bool t)	{
		l = t;
	}
	void right(bool t)	{
		r = t;
	}
	void forward(bool t)	{
		f = t;
	}
	void backward(bool t)	{
		b = t;
	}
	virtual void attack(bool) = 0;
	float getDirection()	{
		return direction;
	}
	Coordinate getLocation()	{
		return location;
	}
	Velocity getVelocity()	{
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
	actorType getType()	{
		return this->type;
	}
	virtual Collision collide(Actor*) = 0;
	virtual void die() = 0;
	float calculateDirectionToActor(Actor* a)	{
		Coordinate pLocation = a->getLocation();
		float diffx = this->location.x - pLocation.x;
		float diffy = this->location.y - pLocation.y;
		if(diffx > 0)	return 360-(180-(R2D(atan(diffy/diffx))));
		else if(diffy > 0)	return 540-(180-(R2D(atan(diffy/diffx))));
		else return	180-(180-(R2D(atan(diffy/diffx))));
	}

	void turnToActor(Actor* a)	{
		float dirToActor = calculateDirectionToActor(a);

		if (direction <= (dirToActor +5) && direction >= (dirToActor -5))	{
			left(false);
			right(false);
			forward(true);
		}
		else if ((dirToActor < direction) && (dirToActor > (direction - 180)))	{
			forward(false);
			left(false);
			right(true);
		}
		else	{
			forward(false);
			right(false);
			left(true);
		}
	}

	void turnFromActor(Actor* a)	{
		float dirToActor = calculateDirectionToActor(a);
		dirToActor += 180;
		if (direction >= 360)	{
			direction -= 360;
		}

		if (direction <= (dirToActor +5) && direction >= (dirToActor -5))	{
			left(false);
			right(false);
			forward(true);
		}
		else if ((dirToActor < direction) && (dirToActor > (direction - 180)))	{
			forward(false);
			left(false);
			right(true);
		}
		else	{
			forward(false);
			right(false);
			left(true);
		}
	}

	bool attacking;

protected:
	int id;
	int lives;
	actorType type;
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
	static const float deceleration;
	AABB bbox;
	int cell;

	virtual Collision detectCollisions() = 0;

private:
};
#endif //__ACTOR_HPP__
