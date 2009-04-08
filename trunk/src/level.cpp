#include "level.hpp"

vector<Cell*>* Level::cellList;
void* Level::level;

Level::Level()	{
	levelNo = 0;
	cellList = new vector<Cell*>();
	enemies = new vector<Actor*>();
	friendlies = new vector<Actor*>();
	loadTextures();
	loadLevel(cellList);
	level = (void*) this;
}

Level::~Level()	{
	//glDisable(GL_BLEND);
	unloadTextures();
	delete this->player;
	delete this->enemies;
	delete this->friendlies;
	delete this->cellList;

}

void Level::gameOver()	{
	/*glClear(GL_COLOR_BUFFER_BIT);
	int i = glutGet(GLUT_ELAPSED_TIME);
	glScalef(5,5,1);
	while(i - glutGet(GLUT_ELAPSED_TIME) < 5000)	{
		renderString(512,334,"Game Over...");
	};
	exit(0);*/ //TODO: Fix the game over section
}

void Level::draw()	{
	vector<Cell*>::iterator cit;
	Cell* c;
	for(cit = cellList->begin(); cit != cellList->end(); ++cit)	{
		c = *cit;
		c->draw();
	}

	vector<Actor*>::iterator ait;
	Actor* a;
	for(ait = friendlies->begin(); ait != friendlies->end(); ++ait)	{
		a = *ait;
		a->draw();
		setCurrentActorCell(a);
	}
	for(ait = enemies->begin(); ait != enemies->end(); ++ait)	{
		a = *ait;
		a->draw();
		setCurrentActorCell(a);
	}
	this->player->draw();
	setCurrentActorCell(this->player);
}

void Level::loadLevel(vector<Cell*>* cellList)	{
	Cell* tempCell;
	int count = 0;
	int cellsize = 256;
	for (int i = 0; i < 3; i++)	{
		for (int j = 0; j < 4; j++)	{
			if(i == 2)	{
				switch(j){
					case 0: tempCell = new Cell(TLCORNER, cellTextures[TLCORNER]);
							break;
					case 1:
					case 2:	tempCell = new Cell(TOP, cellTextures[TOP]);
							break;
					case 3: tempCell = new Cell(TRCORNER, cellTextures[TRCORNER]);
				}
			}
			else if (i == 1)	{
				switch(j){
					case 0: tempCell = new Cell(LEFT, cellTextures[LEFT]);
							break;
					case 1:
					case 2:	tempCell = new Cell(OPEN, cellTextures[OPEN]);
							break;
					case 3: tempCell = new Cell(RIGHT, cellTextures[RIGHT]);
				}
			}
			else if (i == 0)	{
				switch(j){
					case 0: tempCell = new Cell(BLCORNER, cellTextures[BLCORNER]);
							break;
					case 1:
					case 2:	tempCell = new Cell(BOTTOM, cellTextures[BOTTOM]);
							break;
					case 3: tempCell = new Cell(BRCORNER, cellTextures[BRCORNER]);
				}
			}
			tempCell->id = count;
			tempCell->left = (0 + j*cellsize);
			tempCell->right = (cellsize + j*cellsize);
			tempCell->bottom = (0 + i*cellsize);
			tempCell->top = (cellsize + i*cellsize);
			cellList->push_back(tempCell);
			count++;
		}
	}
	this->player = new Player();
	//enemies->push_back(new Enemy(1));
	friendlies->push_back(new Friendly(1));
}

Level* Level::getLevelHandle()	{
	return (Level*)level;
}

void Level::setCurrentActorCell(Actor* a)	{
	Coordinate loc = a->getLocation();
	Cell* c;
	for (vector<Cell*>::iterator it = Level::cellList->begin(); it != Level::cellList->end(); ++it)	{
		c = *it;
		if ((loc.x < c->right) && (loc.x >= c->left) && (loc.y < c->top) && (loc.y >= c->bottom))	{
			int aCell = a->getCurrentCellId();
			if(aCell != -1)	{
				Level::cellList->at(aCell)->unregisterActor(a);
			}
			a->setCurrentCell(c->id);
			c->registerActor(a);
		}
	}
}

void Level::loadTextures()	{
	int numtextures = 10;
	GLuint* texture = new GLuint[numtextures];
	// allocate a texture name
	glGenTextures( numtextures, texture );
	cellTextures[OPEN] =  texture[0];
	loadImage("open.raw", cellTextures[OPEN]);
	cellTextures[FULL] =  texture[1];
	loadImage("full.raw", cellTextures[FULL]);
	cellTextures[TLCORNER] =  texture[2];
	loadImage("tlcorner.raw", cellTextures[TLCORNER]);
	cellTextures[TRCORNER] =  texture[3];
	loadImage("trcorner.raw", cellTextures[TRCORNER]);
	cellTextures[BLCORNER] =  texture[4];
	loadImage("blcorner.raw", cellTextures[BLCORNER]);
	cellTextures[BRCORNER] =  texture[5];
	loadImage("brcorner.raw", cellTextures[BRCORNER]);
	cellTextures[LEFT] =  texture[6];
	loadImage("left.raw", cellTextures[LEFT]);
	cellTextures[RIGHT] =  texture[7];
	loadImage("right.raw", cellTextures[RIGHT]);
	cellTextures[BOTTOM] =  texture[8];
	loadImage("bottom.raw", cellTextures[BOTTOM]);
	cellTextures[TOP] =  texture[9];
	loadImage("top.raw", cellTextures[TOP]);
	delete [] texture;
}

void Level::unloadTextures()	{
	map<cellType,GLuint>::iterator it;
	for (it = cellTextures.begin(); it != cellTextures.end(); ++it)	{
		glDeleteTextures(1, (GLuint*)&((*it).second));
	}
}

bool Level::loadImage(string filename, GLuint& texture)	{
	int width, height;
	FILE * fp;
	string fname = "textures/";
	fname.append(filename);

	// texture data
	width = 256;
	height = 256;

	// open and read texture data
	fp = fopen( fname.c_str(), "rb" );
	if (fp == NULL)	{
		return false;
	}
	unsigned char *image = new unsigned char[width*height*4];
	unsigned char r,g,b,a;

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			r = getc(fp);
			g = getc(fp);
			b = getc(fp);
			a = getc(fp);


			image[i*width*4+j*4]   = r;
			image[i*width*4+j*4+1] = g;
			image[i*width*4+j*4+2] = b;
			image[i*width*4+j*4+3] = a;

			//use code below to incorporate transparency.
			/*if((int)(r&255) >= 250 && (int)(g&255) >= 250 && (int)(b&255) >= 250)
			{
				image[i*width*4+j*4+3] = (GLubyte) 0;
			}
			else
				image[i*width*4+j*4+3] = (GLubyte) 255;*/

		}
	}

	fclose(fp);

	//glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture);
				// Clamp texture coordinates for this texture between 0 and 1
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/*// Texturing Contour Anchored To The Object
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	// Texturing Contour Anchored To The Object
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);			// Auto Texture Generation
	glEnable(GL_TEXTURE_GEN_T);			// Auto Texture Generation*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	delete[] image;	// free image data (no longer used)
	//return texture;
	return true;
}

void Level::killActor(Actor* a)	{
	vector<Actor*>::iterator it;
	actorType at = a->getType();
	switch(at)	{
		case ENEMY:
			for (it = this->enemies->begin(); it != this->enemies->end(); ++it)	{
				if ((*it)->getId() == a->getId())  {
					enemies->erase(it);
					break;
				}
			}
			break;
		case FRIENDLY:
			for (it = this->friendlies->begin(); it != this->friendlies->end(); ++it)	{
				if ((*it)->getId() == a->getId())  {
					friendlies->erase(it);
					break;
				}
			}
			break;
		default:
			break;
	}
}
