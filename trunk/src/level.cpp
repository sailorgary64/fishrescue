#include "level.hpp"

Level::Level()	{
	player = new Player();
	enemy = new Enemy();
	levelNo = 0;
}

Level::~Level()	{
	delete this->player;
}

