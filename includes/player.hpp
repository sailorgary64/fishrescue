#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "actor.hpp"
#include <cmath>

class Player	:	public Actor	{
public:
	Player();
	~Player();
	void draw();
	void left(bool);
	void right(bool);
	void forward(bool);
	void backward(bool);
private:
	float acceleration;
	float deceleration;
	int score;
	GLuint body;
	GLuint tentacles;
};

inline void Player::draw()	{
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
	direction += dTheta;
	if (direction > 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}
	if (f)	{
		dX = acceleration*cos(D2R(direction));
		dY = acceleration*sin(D2R(direction));
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else if (b)	{
		dX = -(acceleration*cos(D2R(direction)));
		dY = -(acceleration*sin(D2R(direction)));
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else {
		velocity.vx *= (1-deceleration);
		velocity.vy *= (1-deceleration);
	}
	velocity.magnitude = sqrt(velocity.vx*velocity.vx + velocity.vy*velocity.vy);
	if(velocity.magnitude > 2)	{
		float tempDecel = 2/velocity.magnitude;
		velocity.vx *= tempDecel;
		velocity.vy *= tempDecel;
	}
	location.x += velocity.vx;
	location.y += velocity.vy;
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(location.x,location.y,0);
	direction += dTheta;
	if (direction > 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}
	glRotatef(direction,0.0,0.0,1.0);
	glCallList(body);
	//glCallList(tentacles);
	glPopMatrix();
	glFlush();
	std::cout << g_fps << std::endl;
};

#endif //__PLAYER_HPP__
