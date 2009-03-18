#ifndef __INCLUDES_HPP__
#define __INCLUDES_HPP__

#include <omp.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

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
} Vector;

typedef struct	{
	Coordinate* c;
	float hwidth;
	float hheight;
} AABB;

typedef struct {
	bool happened;
	float vx;
	float vy;
} Collision;

static void renderString(float x, float y, std::string s)	{
	//glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x,y);
	std::string::iterator it = s.begin();
	while(it != s.end())	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,*it);
		it++;
	}
	glColor3f(0.0,0.0,0.0);
	//glEnable(GL_TEXTURE_2D);
};

static string float2String(float x)	{
	ostringstream s;
	s << x;
	string S;
	S = s.str();
	return S;
}

#endif //__INCLUDES_HPP__
