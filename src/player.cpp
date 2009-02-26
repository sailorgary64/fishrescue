#include "player.hpp"
//#include "game.hpp"

Coordinate Player::location;

Player::Player()	{
	acceleration = 0.05f;
	score = 0;
	lives = 1;
	location.x = 0;
	location.y = 0;
	velocity.vx = 0;
	velocity.vy = 0;
	velocity.magnitude = 0;
	direction = 0;
	dTheta = 0;
	dX = 0;
	dY = 0;
	l = false;
	r = false;
	f = false;
	b = false;
	body = glGenLists(2);
	tentacles = body+1;

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

	glNewList(tentacles, GL_COMPILE);
		glColor3f(0.89,0.54,0.22);
		for(int i = 0; i < 8; i++)	{
			glBegin(GL_POLYGON);
				//TODO:: make legs
			glEnd();
		}
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

Coordinate Player::getLocation()	{
	return location;
}
