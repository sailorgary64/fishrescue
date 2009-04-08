#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "includes.hpp"
#include "cell.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "friendly.hpp"

class Level	{
public:
	Level();
	~Level();
	void draw();
	static Level* getLevelHandle();
	static void gameOver();
	void killActor(Actor*);

	static vector<Cell*>* cellList;
	Actor* player;
	vector<Actor*>* enemies;
	vector<Actor*>* friendlies;

private:
	void loadLevel(vector<Cell*>*);
	void unloadLevel(vector<Cell>*);
	void setCurrentActorCell(Actor*);

	void loadTextures();
	void unloadTextures();
	bool loadImage(string filename, GLuint& texture);
	map<cellType, GLuint> cellTextures;

	int levelNo;
	static void* level;
};

#endif //__LEVEL_HPP__
