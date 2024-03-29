/*
 * friendly.cpp
 *
 *  Created on: Apr 8, 2009
 *      Author: urioxis
 */

#include "friendly.hpp"

Friendly::Friendly(int newId) {
	this->id = newId;
	this->type = FRIENDLY;
	this->playerHandle = Player::getPlayerHandle();
	this->cell = -1;
	score = 0;
	hwidth = 10;
	hheight = 22;
	bbox.hheight = 22;
	bbox.hwidth = 10;
	bbox.c = &this->location;
	acceleration = 0.04f;
	deceleration = 0.01f;
	lives = 1;
	location.x = 600;
	location.y = 1000;
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
	following = false;
	friends = glGenLists(1);
	collision.happened = false;
	collision.vx = 0;
	collision.vy = 0;
	offset.x = 0;
	offset.y = 0;

	glNewList(friends, GL_COMPILE);
		glPushMatrix();
		glColor3f(0.25, 0.5, 0.6);
		glRotatef(90,0.0,0.0,1.0);
		glBegin(GL_POLYGON);	//Body
			glVertex2f(0.0,-23.0);
			glVertex2f(-1.0,-21.6);
			glVertex2f(-2.0,-20.0);
			glVertex2f(-3.2,-17.0);
			glVertex2f(-3.5,-15.0);
			glVertex2f(-3.5,-12.6);
			glVertex2f(-3.3,-10.0);
			glVertex2f(-3.0,-8.0);
			glVertex2f(-2.8,-5.0);
			glVertex2f(-2.5,-3.0);
			glVertex2f(-2.3,-1.0);
			glVertex2f(-2.0,1.0);
			glVertex2f(-1.7,3.0);
			glVertex2f(-1.4,4.5);
			glVertex2f(-1.2,5.2);
			glVertex2f(-1.2,6.0);
			glVertex2f(1.2,6.0);
			glVertex2f(1.2,5.2);
			glVertex2f(1.4,4.5);
			glVertex2f(1.7,3.0);
			glVertex2f(2.0,1.0);
			glVertex2f(2.3,-1.0);
			glVertex2f(2.5,-3.0);
			glVertex2f(2.8,-5.0);
			glVertex2f(3.0,-8.0);
			glVertex2f(3.3,-10.0);
			glVertex2f(3.5,-12.6);
			glVertex2f(3.5,-15.0);
			glVertex2f(3.2,-17.0);
			glVertex2f(2.0,-20.0);
			glVertex2f(1.0,-21.6);
		glEnd();
		glBegin(GL_POLYGON);	//Right fin
			glVertex2f(-3.2,-16.0);
			glVertex2f(-4.0,-15.0);
			glVertex2f(-4.2,-13.5);
			glVertex2f(-4.5,-12.8);
			glVertex2f(-4.8,-12.3);
			glVertex2f(-5.2,-11.9);
			glVertex2f(-5.8,-11.4);
			glVertex2f(-6.0,-10.1);
			glVertex2f(-5.5,-10.0);
			glVertex2f(-4.9,-9.7);
			glVertex2f(-4.0,-9.5);
			glVertex2f(-3.0,-9.0);
		glEnd();
		glBegin(GL_POLYGON);	//tail
			glVertex2f(-1.2,6.0);
			glVertex2f(-0.9,8.5);
			glVertex2f(-0.8,10.0);
			glVertex2f(-0.6,12.0);
			glVertex2f(-0.4,14.5);
			glVertex2f(-0.2,16.0);
			glVertex2f(-0.1,20.0);
			glVertex2f(0.0,23.0);
			glVertex2f(0.1,20.0);
			glVertex2f(0.2,16.0);
			glVertex2f(0.4,14.5);
			glVertex2f(0.6,12.0);
			glVertex2f(0.8,10.0);
			glVertex2f(0.9,8.5);
			glVertex2f(1.2,6.0);
		glEnd();
		glBegin(GL_POLYGON);	//Left fin
			glVertex2f(3.2,-16.0);
			glVertex2f(3.0,-9.0);
			glVertex2f(4.0,-9.5);
			glVertex2f(4.9,-9.8);
			glVertex2f(5.5,-10.0);
			glVertex2f(6.0,-11.1);
			glVertex2f(5.8,-11.4);
			glVertex2f(5.2,-11.9);
			glVertex2f(4.8,-12.3);
			glVertex2f(4.5,-12.8);
			glVertex2f(4.2,-13.5);
			glVertex2f(4.0,-15.0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = -2 + 1024/600 * cos(D2R(i));
				float ycoord = -18 + 1024/600 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 2 + 1024/600 * cos(D2R(i));
				float ycoord = -18 + 1024/600 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(-2, -18);
			glVertex2f(-1.9, -18);
			glVertex2f(1.9, -18);
			glVertex2f(2, -18);
			glVertex2f(2, -19.2);
			glVertex2f(1.9, -19.2);
			glVertex2f(-1.9, -19.2);
			glVertex2f(-2, -19.2);
			glVertex2f(-2, -19.3);
			glVertex2f(-1.9, -19.3);
			glVertex2f(1.9, -19.3);
			glVertex2f(2, -19.3);
		glEnd();
		glPopMatrix();
	glEndList();
}

Friendly::Friendly(Actor* oldActor) {
	this->id = oldActor->getId();
	this->type = FRIENDLY;
	this->playerHandle = Player::getPlayerHandle();
	this->cell = oldActor->getCurrentCellId();
	score = 0;
	hwidth = 10;
	hheight = 22;
	bbox = oldActor->getBBox();
	acceleration = 0.04f;
	deceleration = 0.01f;
	lives = 1;
	location = oldActor->getLocation();
	velocity = oldActor->getVelocity();
	direction = oldActor->getDirection();
	dTheta = 0;
	dX = 0;
	dY = 0;
	l = false;
	r = false;
	f = false;
	b = false;
	friends = glGenLists(1);
	collision.happened = false;
	collision.vx = 0;
	collision.vy = 0;

	glNewList(friends, GL_COMPILE);
		glPushMatrix();
		glColor3f(0.25, 0.5, 0.6);
		glRotatef(90,0.0,0.0,1.0);
		glBegin(GL_POLYGON);	//Body
			glVertex2f(0.0,-23.0);
			glVertex2f(-1.0,-21.6);
			glVertex2f(-2.0,-20.0);
			glVertex2f(-3.2,-17.0);
			glVertex2f(-3.5,-15.0);
			glVertex2f(-3.5,-12.6);
			glVertex2f(-3.3,-10.0);
			glVertex2f(-3.0,-8.0);
			glVertex2f(-2.8,-5.0);
			glVertex2f(-2.5,-3.0);
			glVertex2f(-2.3,-1.0);
			glVertex2f(-2.0,1.0);
			glVertex2f(-1.7,3.0);
			glVertex2f(-1.4,4.5);
			glVertex2f(-1.2,5.2);
			glVertex2f(-1.2,6.0);
			glVertex2f(1.2,6.0);
			glVertex2f(1.2,5.2);
			glVertex2f(1.4,4.5);
			glVertex2f(1.7,3.0);
			glVertex2f(2.0,1.0);
			glVertex2f(2.3,-1.0);
			glVertex2f(2.5,-3.0);
			glVertex2f(2.8,-5.0);
			glVertex2f(3.0,-8.0);
			glVertex2f(3.3,-10.0);
			glVertex2f(3.5,-12.6);
			glVertex2f(3.5,-15.0);
			glVertex2f(3.2,-17.0);
			glVertex2f(2.0,-20.0);
			glVertex2f(1.0,-21.6);
		glEnd();
		glBegin(GL_POLYGON);	//Right fin
			glVertex2f(-3.2,-16.0);
			glVertex2f(-4.0,-15.0);
			glVertex2f(-4.2,-13.5);
			glVertex2f(-4.5,-12.8);
			glVertex2f(-4.8,-12.3);
			glVertex2f(-5.2,-11.9);
			glVertex2f(-5.8,-11.4);
			glVertex2f(-6.0,-10.1);
			glVertex2f(-5.5,-10.0);
			glVertex2f(-4.9,-9.7);
			glVertex2f(-4.0,-9.5);
			glVertex2f(-3.0,-9.0);
		glEnd();
		glBegin(GL_POLYGON);	//tail
			glVertex2f(-1.2,6.0);
			glVertex2f(-0.9,8.5);
			glVertex2f(-0.8,10.0);
			glVertex2f(-0.6,12.0);
			glVertex2f(-0.4,14.5);
			glVertex2f(-0.2,16.0);
			glVertex2f(-0.1,20.0);
			glVertex2f(0.0,23.0);
			glVertex2f(0.1,20.0);
			glVertex2f(0.2,16.0);
			glVertex2f(0.4,14.5);
			glVertex2f(0.6,12.0);
			glVertex2f(0.8,10.0);
			glVertex2f(0.9,8.5);
			glVertex2f(1.2,6.0);
		glEnd();
		glBegin(GL_POLYGON);	//Left fin
			glVertex2f(3.2,-16.0);
			glVertex2f(3.0,-9.0);
			glVertex2f(4.0,-9.5);
			glVertex2f(4.9,-9.8);
			glVertex2f(5.5,-10.0);
			glVertex2f(6.0,-11.1);
			glVertex2f(5.8,-11.4);
			glVertex2f(5.2,-11.9);
			glVertex2f(4.8,-12.3);
			glVertex2f(4.5,-12.8);
			glVertex2f(4.2,-13.5);
			glVertex2f(4.0,-15.0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = -2 + 1024/600 * cos(D2R(i));
				float ycoord = -18 + 1024/600 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i=0; i<360; i+=5)	{
				float xcoord = 2 + 1024/600 * cos(D2R(i));
				float ycoord = -18 + 1024/600 * sin(D2R(i));
				glVertex2f(xcoord, ycoord);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2f(-2, -18);
			glVertex2f(-1.9, -18);
			glVertex2f(1.9, -18);
			glVertex2f(2, -18);
			glVertex2f(2, -19.2);
			glVertex2f(1.9, -19.2);
			glVertex2f(-1.9, -19.2);
			glVertex2f(-2, -19.2);
			glVertex2f(-2, -19.3);
			glVertex2f(-1.9, -19.3);
			glVertex2f(1.9, -19.3);
			glVertex2f(2, -19.3);
		glEnd();
		glPopMatrix();
	glEndList();
}

Friendly::~Friendly() {

}

void Friendly::die()	{
	Cell* c = Level::cellList->at(this->cell);
	c->unregisterActor(this);
	Level* level = (Level*)Level::getLevelHandle();
	level->killActor(this);
}

bool Friendly::playerNearby()	{
	Level* level = (Level*)Level::getLevelHandle();
	if(level->player->getDistance(this->location) < 300)	{
		return true;
	}
	return false;
}

bool Friendly::enemyNearby()	{
	bool enemyNear = false;
	this->closestEnemy = (Actor*)-1;
	Level* level = (Level*)Level::getLevelHandle();
	vector<Actor*>::iterator it;
	Actor* enemy;
	int closestDistance = 1000;	//Arbitrary number sure to be larger than the distance from the enemy
	int distance = 0;

	for(it = level->enemies->begin(); it != level->enemies->end(); ++it)	{
		enemy = *it;
		distance = enemy->getDistance(this->location);
		if(distance < 300)	{
			enemyNear = true;
			if(distance < closestDistance)	{
				this->closestEnemy = enemy;
			}
		}
	}
	return enemyNear;
}

float Friendly::calculatePlayerDirection()	{
	Coordinate pLocation = Level::getLevelHandle()->player->getLocation();
	float diffx = this->location.x - pLocation.x;
	float diffy = this->location.y - pLocation.y;
	if(diffx > 0)	return 360-(180-(R2D(atan(diffy/diffx))));
	else if(diffy > 0)	return 540-(180-(R2D(atan(diffy/diffx))));
	else return	180-(180-(R2D(atan(diffy/diffx))));
}

Collision Friendly::detectCollisions()	{
	Cell* cell = Level::cellList->at(this->cell);
	Coordinate offsetLoc;
	offsetLoc.x = this->location.x - cell->left;
	offsetLoc.y = this->location.y - cell->bottom;
	this->collision = cell->checkCollision(offsetLoc, this->bbox.hwidth, this->velocity);

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
			if(a->getType() == ENEMY)	{
				Coordinate otherLoc = a->getLocation();
				AABB otherBBox = a->getBBox();

				bool xcol = false;
				bool ycol = false;
				if(((location.x + bbox.hwidth) >= (otherLoc.x - otherBBox.hwidth)) || ((location.x - bbox.hwidth <= otherLoc.x + otherBBox.hwidth)))	{
					xcol = true;
				}
				if(((location.y + bbox.hheight) >= (otherLoc.y - otherBBox.hheight)) || ((location.x - bbox.hwidth <= otherLoc.y + otherBBox.hheight)))	{
					ycol = true;
				}
				if(xcol && ycol)	{
					a->collide(this);
					c2 = collide(a);
				}
			}
		}
	}

	if(c2.happened)	{
		collision.happened = true;
		collision.vx += c2.vx;
		collision.vy += c2.vy;
	}

	return collision;
}

Collision Friendly::collide(Actor* obj)	{
	this->collision.happened = true;
	actorType at = obj->getType();
	switch (at)	{
		case PLAYER:
			if(!following)	{
				following = true;
				obj->addScore(50);
			}
			break;

		case ENEMY:
			this->die();
			break;

		default:
			break;
	}
	return this->collision;
}

void Friendly::attack(bool t)	{
}
