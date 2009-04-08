#include "player.hpp"
//#include "game.hpp"

Player* Player::player;

Player::Player()	{
	this->player = this;
	this->id = 0;
	this->type = PLAYER;
	this->cell = -1;
	acceleration = 0.05f;
	deceleration = 0.01f;
	score = 0;
	this->lives = 8;
	location.x = 500;
	location.y = 500;
	velocity.vx = 0;
	velocity.vy = 0;
	velocity.magnitude = 0;
	bbox.c = &location;
	bbox.hwidth = 42;
	bbox.hheight = 21;
	direction = 0;
	dTheta = 0;
	dX = 0;
	dY = 0;
	l = false;
	r = false;
	f = false;
	b = false;
	safetimer = -3000;
	hit = false;
	safe = false;
	flash = false;
	body = glGenLists(2);
	tentacle = body+1;
	attacking = false;
	atkspin = 0;

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

void Player::attack(bool t)	{
	attacking = t;
	atkspin = 0;
}

Collision Player::detectCollisions()	{
	Cell* cell = Level::cellList->at(this->cell);
	vector<Cell*>* cellCheckList = new vector<Cell*>;
	cellCheckList->push_back(cell);
	Coordinate offsetLoc;
	offsetLoc.x = this->location.x - cell->left;
	offsetLoc.y = this->location.y - cell->bottom;

	if(offsetLoc.x + bbox.hwidth > cell->right)	{
		cellCheckList->push_back(Level::cellList->at(this->cell+1));
	}
	if(offsetLoc.x - bbox.hwidth < cell->left)	{
		cellCheckList->push_back(Level::cellList->at(this->cell-1));
	}
	if(offsetLoc.y + bbox.hwidth > cell->top)	{
		cellCheckList->push_back(Level::cellList->at(this->cell+3));
	}
	if(offsetLoc.y - bbox.hwidth < cell->bottom)	{
		cellCheckList->push_back(Level::cellList->at(this->cell-3));
	}
	//No need to worry about array bounds as the cells at the edge of the level and therefore the edge
	//of the array cannot have the player overlapping any edges that would cause a problem.

	Collision c;
	c.happened = false;
	c.vx = 0;
	c.vy = 0;

	for (vector<Cell*>::iterator it = cellCheckList->begin(); it != cellCheckList->end(); ++it)	{
		Collision c1;
		c1 = cell->checkCollision(offsetLoc, this->bbox.hwidth, this->velocity);
		Collision c2;
		c2.happened = false;
		c2.vx = 0;
		c2.vy = 0;

		int s = cell->actors.size();
		if(s > 1)	{
			map<int,Actor*>::iterator it;
			Actor* a;
			for (it = cell->actors.begin(); it != cell->actors.end(); ++it)	{
				a = (*it).second;
				if(a->getId() != this->id)	{
					float dist = a->getDistance(this->location);
					if(dist < this->bbox.hheight)	{
						a->collide(this);
						c2 = collide(a);
					}
				}
			}
		}
		if (c1.happened)	{
			c.happened = true;
			c.vx += c1.vx;
			c.vy += c1.vy;
		}
		if (c2.happened)	{
			c.happened = true;
			c.vx += c2.vx;
			c.vy += c2.vy;
		}
	}
	return c;
}

Collision Player::collide(Actor* obj)	{
	Collision c;
	actorType at = obj->getType();
	switch(at)	{
		case ENEMY:
			if(!safe && !attacking)	{
				this->lives--;
				if(lives <= 0)	{
					Level::gameOver();
				}
				safetimer = glutGet(GLUT_ELAPSED_TIME);
				c.happened = true;
				Velocity veloc = obj->getVelocity();
				c.vx = veloc.vx;
				c.vy = veloc.vy;
				hit = true;
				safe = true;
			}
			else {
				if(attacking)	{
					obj->die();
					score += 200;
				}
				c.happened = false;
				c.vx = 0;
				c.vy = 0;
			}
			break;

		case FRIENDLY:
			c.happened = false;	//Though a collision occurred, we ignore it. These fish are friends :)
			c.vx = 0;
			c.vy = 0;
			score += 50;
			break;

		default:
			c.happened = false;
			c.vx = 0;
			c.vy = 0;
			break;
	}

	return c;
}

void Player::die()	{

}
