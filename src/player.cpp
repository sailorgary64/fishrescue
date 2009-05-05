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
	location.x = 700;
	location.y = 200;
	velocity.vx = 0;
	velocity.vy = 0;
	velocity.magnitude = 0;
	hwidth = 42;
	hheight = 21;
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
	sucked = false;
	offset.x = 0;
	offset.y = 0;
	wpLoc.x = 0;
	wpLoc.y = 0;

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
	Cell* tempcell = Level::cellList->at(this->cell);
	vector<Cell*>* cellCheckList = new vector<Cell*>;
	cellCheckList->push_back(tempcell);
	Coordinate offsetLoc;
	offsetLoc.x = this->location.x - tempcell->left;
	offsetLoc.y = this->location.y - tempcell->bottom;

	if(offsetLoc.x + hwidth > tempcell->right)	{
		cellCheckList->push_back(Level::cellList->at(this->cell+1));
	}
	if(offsetLoc.x - hwidth < tempcell->left)	{
		if(this->cell > 0)	cellCheckList->push_back(Level::cellList->at(this->cell-1));
	}
	if(offsetLoc.y + hwidth > tempcell->top)	{
		cellCheckList->push_back(Level::cellList->at(this->cell+4));		//TODO: Change 4 to be a variable that is
	}																		//		the number of cells in a row
	if(offsetLoc.y - hwidth < tempcell->bottom)	{
		if(this->cell > 3) cellCheckList->push_back(Level::cellList->at(this->cell-4));
	}
	if((offsetLoc.x - hwidth < tempcell->left) && (offsetLoc.y + hwidth > tempcell->top))	{
		cellCheckList->push_back(Level::cellList->at(this->cell + 3));
	}
	if((offsetLoc.x + hwidth > tempcell->right) && (offsetLoc.y + hwidth > tempcell->top))	{
		cellCheckList->push_back(Level::cellList->at(this->cell + 5));		//TODO: Sort this stuff out
	}
	if((offsetLoc.x - hwidth > tempcell->left) && (offsetLoc.y - hwidth < tempcell->bottom))	{
		if(this->cell > 4) cellCheckList->push_back(Level::cellList->at(this->cell - 5));
	}
	if((offsetLoc.x + hwidth > tempcell->right) && (offsetLoc.y - hwidth < tempcell->bottom))	{
		if(this->cell > 2) cellCheckList->push_back(Level::cellList->at(this->cell - 3));
	}
	//No need to worry about array bounds as the cells at the edge of the level and therefore the edge
	//of the array cannot have the player overlapping any edges that would cause a problem.

	Collision c;
	c.happened = false;
	c.vx = 0;
	c.vy = 0;

	Collision c1;
	c1 = tempcell->checkCollision(offsetLoc, this->bbox.hwidth, this->velocity);

	for (vector<Cell*>::iterator it = cellCheckList->begin(); it != cellCheckList->end(); ++it)	{
		tempcell = *it;
		Collision c2;
		c2.happened = false;
		c2.vx = 0;
		c2.vy = 0;
		int s = tempcell->actors.size();
		if(s > 1)	{
			map<int,Actor*>::iterator mit;
			Actor* a;
			for (mit = tempcell->actors.begin(); mit != tempcell->actors.end(); ++mit)	{
				a = (*mit).second;
				if(a->getId() != this->id)	{
					float dist = a->getDistance(this->location);
					AABB theirBox = a->getBBox();
					dist -= theirBox.hwidth;
					if(dist < this->bbox.hheight)	{		//TODO: sort out bounding boxes
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
			break;

		case POOL:
			c.happened = true;
			sucked = true;
			c.vx = 0;
			c.vy = 0;
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

void Player::finishLevel()	{
	Level* level = (Level*)Level::getLevelHandle();
	score += 500;	//TODO: Get extra score for time bonus and for leading fish to exit
	level->finished();
}
