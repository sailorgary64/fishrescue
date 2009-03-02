#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "actor.hpp"

class Player	:	public Actor	{
public:
	Player();
	~Player();
	void draw();
	void left(bool);
	void right(bool);
	void forward(bool);
	void backward(bool);
	void collide(Actor*);

private:
	void detectCollisions();
	//static Coordinate location;
	float acceleration;
	float deceleration;
	int score;
	float dtheta;
	float direction;
	GLuint body;
	GLuint tentacle;
};

inline void Player::draw()	{
	int currentFps = Fps::getFps();
	if (currentFps < 1)	{
		currentFps = 1;
	}
	if (l)	{
		if (dTheta <= 1.1)	{
			dTheta += 0.02;
		}
	}
	else if (r)	{
		if (dTheta >= -1.1)	{
			dTheta -= 0.02;
		}
	}
	else {
		dTheta /= 1.1;
		if (dTheta < 0.3 && dTheta > -0.3)	{
			dTheta = 0;
		}
	}
	direction += dTheta * (250/currentFps);
	if (direction >= 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}
	if (f)	{
		dX = acceleration*cos(D2R(direction));
		dY = acceleration*sin(D2R(direction));
		dX *= (250/currentFps);
		dY *= (250/currentFps);
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else if (b)	{
		dX = -(acceleration*cos(D2R(direction)));
		dY = -(acceleration*sin(D2R(direction)));
		dX *= (250/currentFps);
		dY *= (250/currentFps);
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else {
		velocity.vx *= ((1-deceleration)*(250/currentFps));
		velocity.vy *= ((1-deceleration)*(250/currentFps));
	}
	velocity.magnitude = sqrt(velocity.vx*velocity.vx + velocity.vy*velocity.vy);
	if(velocity.magnitude > 2)	{
		float tempDecel = (2/velocity.magnitude)*(250/currentFps);
		velocity.vx *= tempDecel;
		velocity.vy *= tempDecel;
	}
	location.x += velocity.vx;
	location.y += velocity.vy;
	
	string s = "Player cell: ";
	s.append(float2String(this->cell));
	renderString(700,730,s);


	glPushMatrix();
	glTranslatef(location.x,location.y,0);
	direction += dTheta;
	if (direction > 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}
	glRotatef(direction,0.0,0.0,1.0);
	glRotatef(180,0.0,0.0,1.0);
	for (int i = 0; i < lives; i++)	{
		int tentacleAngle = ((360/lives)*i);
		glRotatef(tentacleAngle, 0.0, 0.0, 1.0);
		glCallList(tentacle);
	}
	glCallList(body);
	glPopMatrix();
};

#endif //__PLAYER_HPP__
