#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "includes.hpp"
#include "player.hpp"
#include "enemy.hpp"

class Level	{
public:
	Level();
	~Level();
	void draw();
	Player* player;
	Enemy* enemy;
private:
	void loadLevel();
	void unloadLevel();
	int levelNo;
};

inline void Level::draw()	{
	this->enemy->draw();
	this->player->draw();
}

#endif //__LEVEL_HPP__
