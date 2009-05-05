#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "actor.hpp"
#include "level.hpp"

class Player	:	public Actor	{
public:
	Player();
	~Player();
	void draw(Coordinate);
	void attack(bool);
	Collision collide(Actor*);
	void die();
	void setScreen(int width, int height)	{
		screenWidth = width;
		screenHeight = height;
	}
	static Player* getPlayerHandle()	{
		return player;
	}

private:
	static Player* player;
	int screenWidth;
	int screenHeight;
	void drawPlayer();
	Collision detectCollisions();
	void finishLevel();
	//static Coordinate location;
	float acceleration;
	float deceleration;
	float dtheta;
	GLuint body;
	GLuint tentacle;
	int safetimer;
	int atktimer;
	int atkspin;
	bool hit;
	bool safe;
	bool flash;
	bool sucked;
};

inline void Player::draw(Coordinate unused)	{
	glColor3f(1,1,1);
	string s;
	s.assign("Score: ");
	s.append(int2String(score));
	renderString(412, 354, s);

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
	direction += dTheta;
	if (direction >= 360)	{
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
		velocity.vx *= ((1-deceleration));
		velocity.vy *= ((1-deceleration));
	}
	velocity.magnitude = sqrt(velocity.vx*velocity.vx + velocity.vy*velocity.vy);
	if(velocity.magnitude > 2)	{
		float tempDecel = (2/velocity.magnitude);
		velocity.vx *= tempDecel;
		velocity.vy *= tempDecel;
	}
	if(this->cell != -1)	{
		Collision collision = detectCollisions();
		if(collision.happened)	{
			velocity.vx = collision.vx;
			velocity.vy = collision.vy;
		}
	}

	if(sucked)	{
		Coordinate dw;
		dw.x = wpLoc.x - location.x;
		dw.y = wpLoc.y - location.y;
		if(abs(dw.x) < 10 && abs(dw.y) < 10)	{
			velocity.vx = 0;
			velocity.vy = 0;
			location.x = wpLoc.x;
			location.y = wpLoc.y;
			finishLevel();
		}
		else	{
			velocity.vx = dw.x * 0.2;
			velocity.vy = dw.y * 0.2;
		}
	}
	location.x += velocity.vx;
	location.y += velocity.vy;

	if(attacking)	{
		int atkspeed = 6;
		atkspin += atkspeed;
		if(atkspeed < 0)	{
			attacking = false;
		}
		if (atkspin >= 180)	{
			atkspeed -= 0.0001;
		}
		if (atkspin > 360)	{
			atkspin -= 360;
			atkspeed -= 0.0001;
		}
		bbox.hheight = 42;
	}
	else	{
		bbox.hheight = 25;
	}

	if(hit)	{
		if(glutGet(GLUT_ELAPSED_TIME) - safetimer > 3000)	{
			hit = false;
			safe = false;
		}
		if(!flash)	{
			flash = true;
		}
		else	{
			drawPlayer();
			flash = false;
		}
	}
	else	{
		drawPlayer();
	}
};

inline void Player::drawPlayer()	{
	glPushMatrix();
		direction += dTheta;
		if (direction > 360)	{
			direction -= 360;
		}
		if (direction < 0)	{
			direction += 360;
		}
		glTranslatef(offset.x,offset.y,0);
		glRotatef(direction,0.0,0.0,1.0);
		for (int i = 0; i < 8; i++)	{
			glPushMatrix();
				glLoadIdentity();
				glTranslatef(offset.x,offset.y,0);
				glRotatef(direction + atkspin,0.0,0.0,1.0);
				int tentacleAngle = ((360/lives)*i);
				glRotatef(tentacleAngle, 0.0, 0.0, 1.0);
				glCallList(tentacle);
			glPopMatrix();
		}
		glCallList(body);
	glPopMatrix();
}

#endif //__PLAYER_HPP__
