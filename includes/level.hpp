#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "includes.hpp"
#include "cell.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "friendly.hpp"
#include "whirlpool.hpp"

class Level	{
public:
	Level(int width, int height);
	~Level();
	void draw();
	static Level* getLevelHandle();
	static void gameOver();
	void killActor(Actor*);
	int getWidth()	{
		return screenWidth;
	}
	int getHeight()	{
		return screenHeight;
	}
	Coordinate getPlayerLocation()	{
		return player->getLocation();
	}
	void finished();

	static vector<Cell*>* cellList;
	Actor* player;
	vector<Actor*>* enemies;
	vector<Actor*>* friendlies;
	int screenWidth;
	int screenHeight;
	Whirlpool* whirlpool;

private:
	void newLevel(int);
	void loadLevel();
	void unloadLevel(vector<Cell>*);
	void setCurrentActorCell(Actor*);

	void loadTextures();
	void unloadTextures();
	bool loadImage(string filename, GLuint& texture);
	map<cellType, GLuint> cellTextures;

	int levelNo;
	int levelWidth;
	int levelHeight;
	static void* level;
	Coordinate playerLocation;
};

#endif //__LEVEL_HPP__
