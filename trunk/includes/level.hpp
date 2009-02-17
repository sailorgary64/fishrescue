#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "includes.hpp"
#include "player.hpp"

class Level	{
public:
	Level();
	~Level();
	void draw();
	Player* player;
private:
	void loadLevel();
	void unloadLevel();
	int levelNo;
};

inline void Level::draw()	{
	this->player->draw();
}

#endif //__LEVEL_HPP__