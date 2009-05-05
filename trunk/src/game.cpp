#include "game.hpp"
#include "fps.hpp"

void* Game::game;

Game::Game(int width, int height)	{
	input = new Input();
	level = new Level(width, height);
	angle = 0;
	this->game = (void*) this;
	fps = new Fps();
	currentTime = 0;
	lastTime = 0;
	this->screenHeight = height;
	this->screenWidth = width;
	updateWorld = true;
}

Game::~Game()	{
	delete this->input;
	delete this->level;
	delete this->fps;
}

/*void Game::setMode(int width, int height)	{
	this->screenHeight = height;
	this->screenWidth = width;
}*/

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
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	if ((currentTime - lastTime) >= 1000/250)	{
		if(updateWorld)	{
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(-screenWidth/2, screenWidth/2, -screenHeight/2, screenHeight/2);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//glTranslatef(screenWidth/2, screenHeight/2, 0);
			this->level->draw();
			//gluLookAt(0, 0 , 5, playerLoc.x, playerLoc.y, 0, 0, 1, 0);
			fps->frameExecuted();
			fps->displayFps();
			//glFlush();
			glutSwapBuffers();
			//Check to see if any keys have been pressed and deal with them
			//before rendering the next frame
		}
		while(Input::checkKeyBuffer())	{
			Input::keyPress k = *Input::popKey();
			switch(k.nKey)	{
				case 27:
					exit(0);
					break;
				case 32:
					level->player->attack(k.pressed);
					break;
				case 112:
					if(updateWorld)	{
						updateWorld = false;
					}
					else	{
						updateWorld = true;
					}
					break;
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
		lastTime=glutGet(GLUT_ELAPSED_TIME);
	}
}
