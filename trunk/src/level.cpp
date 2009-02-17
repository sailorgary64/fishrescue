#include "level.hpp"

Level::Level()	{
	player = new Player();
	levelNo = 0;
}

Level::~Level()	{
	delete this->player;
}

