#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "includes.hpp"
#include "input.hpp"
#include "level.hpp"
#include "fps.hpp"

class Game	{
public:
	Game();
	~Game();

	static void displayWrapper();
	void display();		//Main display function
	void setMode(int width, int height);
	static int getScreenWidth();
	static int getScreenHeight();

private:
	static void* game;
	Input* input;
	Level* level;
	float angle;
	int screenWidth;
	int screenHeight;
	Fps* fps;
	int currentTime;
	int lastTime;
};

#endif //__GAME_HPP__
