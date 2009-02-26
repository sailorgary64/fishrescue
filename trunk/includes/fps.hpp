/*
 * fps.hpp
 *
 *  Created on: Feb 18, 2009
 *      Author: urioxis
 */

#ifndef __FPS_HPP__
#define __FPS_HPP__

#include "includes.hpp"

class Fps	{
public:
	Fps();
	~Fps();
	void frameExecuted();
	void displayFps();
	static int getFps();
private:
	int frame;
	int time;
	int timebase;
	static int fps;
};

#endif /* __FPS_HPP__ */

