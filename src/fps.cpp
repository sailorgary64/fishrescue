/*
 * fps.cpp
 *
 *  Created on: Feb 18, 2009
 *      Author: urioxis
 */

#include "fps.hpp"
/*
int Fps::frame;
int Fps::time;
int Fps::timebase;*/
int Fps::fps;

Fps::Fps()	{
	fps = 0;
	time = 0;
	timebase = 0;
	frame = 0;
}

Fps::~Fps()	{

}

void Fps::frameExecuted()	{
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		timebase = time;
		frame = 0;
	}
}

void Fps::displayFps()	{
	std::string s = "FPS: ";
	std::ostringstream stm;
	stm << fps;
	s.append(stm.str());
	renderString(10, 768-20, s);
}

int Fps::getFps()	{
	return fps;
}
