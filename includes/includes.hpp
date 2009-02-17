#ifndef __INCLUDES_HPP__
#define __INCLUDES_HPP__

#include <omp.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

#define PI 3.1415926
#define R2D(rad) ((180.0 * rad) / PI)
#define D2R(deg) ((deg * PI) / 180.0)

typedef struct	{
	float x;
	float y;
} Coordinate;

typedef struct	{
	float vx;
	float vy;
	float magnitude;
} Velocity;

static float g_fps;

static void renderString(float x, float y, std::string s)	{
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x,y);
	std::string::iterator it = s.begin();
	while(it != s.end())	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,*it);
		it++;
	}
};

#endif //__INCLUDES_HPP__