#include "player.hpp"
//#include "game.hpp"

Player::Player()	{
	acceleration = 0.05f;
	deceleration = 0.01f;
	score = 0;
	lives = 8;
	location.x = 0;
	location.y = 0;
	velocity.vx = 0;
	velocity.vy = 0;
	velocity.magnitude = 0;
	bbox.c = &location;
	bbox.hwidth = 70;
	bbox.hheight = 70;
	direction = 0;
	dTheta = 0;
	dX = 0;
	dY = 0;
	l = false;
	r = false;
	f = false;
	b = false;
	body = glGenLists(2);
	tentacle = body+1;

	glNewList(body,GL_COMPILE);
		glColor3f(0.89,0.54,0.22);
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 0 + 1024/50 * cos(D2R(i));
				float ycoord = 0 + 1024/50 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 15 + 1024/200 * cos(D2R(i));
				float ycoord = 5 + 1024/200 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 15 + 1024/200 * cos(D2R(i));
				float ycoord = -5 + 1024/200 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(17, 5);
			glVertex2f(18, 5);
			glVertex2f(18, 4);
			glVertex2f(18, -4);
			glVertex2f(18, -5);
			glVertex2f(17, -5);
			glVertex2f(17, -4);
			glVertex2f(17, +4);
		glEnd();
	glEndList();

	glNewList(tentacle, GL_COMPILE);
		glColor3f(0.79,0.44,0.12);
		glBegin(GL_POLYGON);
			glVertex2f(1024/200 + 10, 5);
			glVertex2f(1024/200 + 30, 8);
			glVertex2f(1024/200 + 30, -8);
			glVertex2f(1024/200 + 10, -5);
		glEnd();
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 35 + 1024/120 * cos(D2R(i));
				float ycoord = 1024/120 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
	glEndList();
}

Player::~Player()	{
}

void Player::left(bool t)	{
	l = t;
}

void Player::right(bool t)	{
	r = t;
}

void Player::forward(bool t)	{
	f = t;
}

void Player::backward(bool t)	{
	b = t;
}

void Player::detectCollisions()	{
	
}

void Player::collide(Actor* obj)	{
	int currentFps = Fps::getFps();
	this->lives--;
	dX = acceleration*cos(D2R(obj->getDirection()));
	dY = acceleration*sin(D2R(obj->getDirection()));
	dX *= (250/currentFps);
	dY *= (250/currentFps);
	velocity.vx += dX;
	velocity.vy += dY;
}