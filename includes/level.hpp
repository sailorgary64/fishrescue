#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "includes.hpp"
#include "player.hpp"
#include "enemy.hpp"

class Level	{
public:
	typedef struct	{
		int id;
		float left;
		float right;
		float top;
		float bottom;
		vector<Actor*>* actors;
	} Cell;

	Level();
	~Level();
	void draw();
	static Level* getLevelHandle();

	static vector<Cell>* cellList;
	Actor* player;

private:
	void loadLevel(vector<Cell>*);
	void unloadLevel(vector<Cell>*);
	void setCurrentActorCell(Actor*);

	int levelNo;
	vector<Actor*>* enemies;
	static void* level;
};

#endif //__LEVEL_HPP__
