#include "level.hpp"

vector<Level::Cell>* Level::cellList;
void* Level::level;

Level::Level()	{
	levelNo = 0;
	cellList = new vector<Cell>();
	enemies = new vector<Actor*>();
	loadLevel(cellList);
	level = (void*) this;
}

Level::~Level()	{
	delete this->player;
}

void Level::draw()	{
	vector<Actor*>::iterator it;
	Actor* a;
	for(it = enemies->begin(); it != enemies->end(); ++it)	{
		a = *it;
		a->draw();
		setCurrentActorCell(a);
	}
	this->player->draw();
	setCurrentActorCell(this->player);
}

void Level::loadLevel(vector<Cell>* cellList)	{
	Cell tempCell;
	int count = 0;
	for (int i = 0; i < 8; i++)	{
		for (int j = 0; j < 6; j++)	{
			tempCell.id = count;
			tempCell.left = (0 + i*128);
			tempCell.right = (128 + i*128);
			tempCell.bottom = (0 + j*128);
			tempCell.top = (128 + j*128);
			tempCell.actors = new vector<Actor*>();
			cellList->push_back(tempCell);
			count++;
		}
	}
	cellList->at(12).actors->push_back(new Enemy());
	enemies->push_back(cellList->at(12).actors->at(0));
	cellList->at(40).actors->push_back(new Player());
	this->player = cellList->at(40).actors->at(0);
}

Level* Level::getLevelHandle()	{
	return (Level*)level;
}

void Level::setCurrentActorCell(Actor* a)	{
	Coordinate loc = a->getLocation();
	Cell c;
	for (vector<Cell>::iterator it = Level::cellList->begin(); it != Level::cellList->end(); ++it)	{
		c = *it;
		if ((loc.x < c.right) && (loc.x >= c.left) && (loc.y < c.top) && (loc.y >= c.bottom))	{
			a->setCurrentCell(c.id);
		}
	}
}
