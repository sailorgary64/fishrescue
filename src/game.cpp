#include "game.hpp"
#include "fps.hpp"

void* Game::game;

Game::Game()	{
	input = new Input();
	level = new Level();
	angle = 0;
	this->game = (void*) this;
	fps = new Fps();
}

Game::~Game()	{
	delete this->input;
	delete this->level;
}

void Game::setMode(int width, int height)	{
	this->screenHeight = height;
	this->screenWidth = width;
}

int Game::getScreenHeight()	{
	Game* g = (Game*) Game::game;
	return g->screenHeight;
}

int Game::getScreenWidth()	{
	Game* g = (Game*) Game::game;
	return g->screenWidth;
}

void Game::displayWrapper()	{
	Game* g = (Game*) Game::game;
	g->display();
}

void Game::display()	{
	glClear(GL_COLOR_BUFFER_BIT);
	/*glPushMatrix();
	glRotatef(angle,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();
	glPopMatrix();
	glFlush();
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	this->level->draw();
	fps->frameExecuted();
	fps->displayFps();
	glFlush();
	glutSwapBuffers();

	//Check to see if any keys have been pressed and deal with them
	//before rendering the next frame
	while(Input::checkKeyBuffer())	{
		Input::keyPress k = *Input::popKey();
		switch(k.nKey)	{
			case 27:
				exit(0);
			default:
				break;
		}
		switch(k.sKey)	{
			case GLUT_KEY_LEFT:
				level->player->left(k.pressed);
				break;
			case GLUT_KEY_RIGHT:
				level->player->right(k.pressed);
				break;
			case GLUT_KEY_UP:
				level->player->forward(k.pressed);
				break;
			case GLUT_KEY_DOWN:
				level->player->backward(k.pressed);
				break;
			default:
				break;
		}
	}
}
