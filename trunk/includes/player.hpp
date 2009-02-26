#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "actor.hpp"
//#include "fps.hpp"

class Player	:	public Actor	{
public:
	Player();
	~Player();
	void draw();
	void left(bool);
	void right(bool);
	void forward(bool);
	void backward(bool);
	static Coordinate getLocation();

private:
	static Coordinate location;
	float acceleration;
	int score;
	float dtheta;
	float direction;
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
	direction += dTheta / (250/(Fps::getFps()+1));
	if (direction >= 360)	{
		direction -= 360;
	}
	if (direction < 0)	{
		direction += 360;
	}
	if (f)	{
		dX = acceleration*cos(D2R(direction));
		dY = acceleration*sin(D2R(direction));
		dX /= (250/(Fps::getFps()+1));
		dY /= (250/(Fps::getFps()+1));
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else if (b)	{
		dX = -(acceleration*cos(D2R(direction)));
		dY = -(acceleration*sin(D2R(direction)));
		dX /= (250/(Fps::getFps()+1));
		dY /= (250/(Fps::getFps()+1));
		velocity.vx += dX;
		velocity.vy += dY;
	}
	else {
		velocity.vx *= ((1-deceleration)/(250/(Fps::getFps()+1)));
		velocity.vy *= ((1-deceleration)/(250/(Fps::getFps()+1)));
	}
	velocity.magnitude = sqrt(velocity.vx*velocity.vx + velocity.vy*velocity.vy);
	if(velocity.magnitude > 2)	{
		float tempDecel = (2/velocity.magnitude)/(250/(Fps::getFps()+1));
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
};

#endif //__PLAYER_HPP__
