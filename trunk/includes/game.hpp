#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "includes.hpp"
#include "input.hpp"
#include "level.hpp"

class Game	{
public:
	Game();
	~Game();

	static void displayWrapper();
	void display();		//Main display function
	void setMode(int width, int height);
	static int getScreenWidth();
	static int getScreenHeight();
	float fps;

private:
	static void* game;
	Input* input;
	Level* level;
	float angle;
	int screenWidth;
	int screenHeight;
	int frame;
	int time;
	int timebase;
	void frameExecuted();
	void displayFps();
};

inline void Game::frameExecuted()	{
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		timebase = time;
		frame = 0;
	}
	g_fps = fps;
}

inline void Game::displayFps()	{
	std::string s = "FPS: ";
	std::ostringstream stm;
	stm << fps;
	s.append(stm.str());
	renderString(10, 768-20, s);
}

#endif //__GAME_HPP__
