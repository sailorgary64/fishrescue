#include "level.hpp"

vector<Cell*>* Level::cellList;
void* Level::level;

Level::Level(int width, int height) {
	loadTextures();
	screenWidth = width;
	screenHeight = height;
	levelNo = 0;
	newLevel(levelNo);
	level = (void*) this;
}

Level::~Level() {
	//glDisable(GL_BLEND);
	unloadTextures();
	delete this->player;
	delete this->enemies;
	delete this->friendlies;
	delete this->cellList;

}

void Level::newLevel(int levelNum) {
	levelNo = levelNum;
	cellList = new vector<Cell*> ();
	enemies = new vector<Actor*> ();
	friendlies = new vector<Actor*> ();
	this->player = new Player();
	player->setScreen(this->screenWidth, this->screenHeight);
	loadLevel();
}

void Level::finished() {
	delete cellList;
	delete enemies;
	delete friendlies;
	newLevel(levelNo + 1);
}

void Level::gameOver() {
	/*glClear(GL_COLOR_BUFFER_BIT);
	 int i = glutGet(GLUT_ELAPSED_TIME);
	 glScalef(5,5,1);
	 while(i - glutGet(GLUT_ELAPSED_TIME) < 5000)	{
	 renderString(512,334,"Game Over...");
	 };
	 exit(0);*///TODO: Fix the game over section
}

void Level::draw() {
	Coordinate playerLoc = player->getLocation();
	Coordinate offset;
	offset.x = 0;
	offset.y = 0;

	if(playerLoc.x >= 512 && playerLoc.x <= levelWidth)	{
		playerLocation.x = playerLoc.x;
	}
	else if (playerLoc.x < 512)	{
		offset.x = -(512-playerLoc.x);
		playerLocation.x = 512;
	}
	else {
		offset.x = playerLoc.x - 512;
		playerLocation.x = levelWidth;
	}

	if(playerLoc.y >= 384 && playerLoc.y <= levelHeight)	{
		playerLocation.y = playerLoc.y;
	}
	else if (playerLoc.y < 384)	{
		playerLocation.y = 384;
		offset.y = -(384-playerLoc.y);
	}
	else {
		playerLocation.y = levelHeight;
		offset.y = playerLoc.y - levelHeight;
	}

	player->setOffset(offset);
	Coordinate whirlPoolLoc = whirlpool->getLocation();
	vector<Cell*>::iterator cit;
	Cell* c;
	for (cit = cellList->begin(); cit != cellList->end(); ++cit) {
		c = *cit;
		c->draw(playerLocation);
	}
	if(abs(playerLocation.x - whirlPoolLoc.x) < 600 && abs(playerLocation.y - whirlPoolLoc.y) < 400)	{
			whirlpool->draw(playerLocation);
			setCurrentActorCell(whirlpool);
	}
	//TODO: Fix this seg fault
	vector<Actor*>::iterator ait;
	Actor* a;
	for (ait = friendlies->begin(); ait != friendlies->end(); ++ait) {
		a = *ait;
		a->draw(playerLocation);
		setCurrentActorCell(a);
	}
	for (ait = enemies->begin(); ait != enemies->end(); ++ait) {
		a = *ait;
		a->draw(playerLocation);
		setCurrentActorCell(a);
	}
	this->player->draw(playerLocation);
	setCurrentActorCell(this->player);
}

void Level::loadLevel() {
	Cell* tempCell;
	int count = 0;
	int cellsize = 256;
	Coordinate loc;
	loc.x = 0;
	loc.y = 0;
	switch (levelNo) {
	case 0:
		levelWidth = ((4*cellsize)-512);
		levelHeight = ((5*cellsize)-384);
		for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 4; j++) {
						switch (i) {
						case 4:
							switch (j) {
							case 0:
							case 1:
							case 2:
							case 3:
								tempCell = new Cell(FULL,
										cellTextures[FULL]);
							}
							break;

						case 3:
							switch (j) {
							case 0:
							case 1:
							case 2:
							case 3:
								tempCell = new Cell(FULL,
										cellTextures[FULL]);
							}
							break;

						case 2:
							switch (j) {
							case 0:
								tempCell = new Cell(TLCCCORNER, cellTextures[TLCCCORNER]);
								break;
							case 1:
								tempCell = new Cell(TOP, cellTextures[TOP]);
								break;
							case 2:
								tempCell = new Cell(TOP, cellTextures[TOP]);
								break;
							case 3:
								tempCell = new Cell(TRCCCORNER, cellTextures[TRCCCORNER]);
							}
							break;

						case 1:
							switch (j) {
							case 0:
								tempCell = new Cell(BLCCCORNER, cellTextures[BLCCCORNER]);
								break;
							case 1:
								tempCell = new Cell(BOTTOM,
										cellTextures[BOTTOM]);
								break;
							case 2:
								tempCell = new Cell(BOTTOM, cellTextures[BOTTOM]);
								break;
							case 3:
								tempCell = new Cell(BRCCCORNER,
										cellTextures[BRCCCORNER]);
							}
							break;

						case 0:
							switch (j) {
							case 0:
							case 1:
							case 2:
							case 3:
								tempCell = new Cell(FULL,
										cellTextures[FULL]);
							}
							break;
						}
						tempCell->id = count;
						tempCell->left = (0 + j * cellsize);
						tempCell->right = (cellsize + j * cellsize);
						tempCell->bottom = (0 + i * cellsize);
						tempCell->top = (cellsize + i * cellsize);
						cellList->push_back(tempCell);
						count++;
					}
				}
				loc.x = 200;
				loc.y = 500;
				player->setLocation(loc);
				this->whirlpool = new Whirlpool(800,500);
				player->setwpLoc(whirlpool->getLocation());
				break;
	case 1:
		levelWidth = (4*cellsize-512);
		levelHeight = (5*cellsize-384);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 4; j++) {
				switch (i) {
				case 4:
					switch (j) {
					case 0:
						tempCell = new Cell(TLCCCORNER,
								cellTextures[TLCCCORNER]);
						break;
					case 1:
					case 2:
						tempCell = new Cell(TOP, cellTextures[TOP]);
						break;
					case 3:
						tempCell = new Cell(TRCCCORNER,
								cellTextures[TRCCCORNER]);
					}
					break;

				case 3:
					switch (j) {
					case 0:
						tempCell = new Cell(LEFT, cellTextures[LEFT]);
						break;
					case 1:
						tempCell = new Cell(TLCVCORNER,
								cellTextures[TLCVCORNER]);
						break;
					case 2:
						tempCell = new Cell(BOTTOM, cellTextures[BOTTOM]);
						break;
					case 3:
						tempCell = new Cell(BRCCCORNER,
								cellTextures[BRCCCORNER]);
					}
					break;

				case 2:
					switch (j) {
					case 0:
						tempCell = new Cell(LEFT, cellTextures[LEFT]);
						break;
					case 1:
						tempCell = new Cell(RIGHT, cellTextures[RIGHT]);
						break;
					case 2:
						tempCell = new Cell(FULL, cellTextures[FULL]);
						break;
					case 3:
						tempCell = new Cell(FULL, cellTextures[FULL]);
					}
					break;

				case 1:
					switch (j) {
					case 0:
						tempCell = new Cell(LEFT, cellTextures[LEFT]);
						break;
					case 1:
						tempCell = new Cell(BLCVCORNER,
								cellTextures[BLCVCORNER]);
						break;
					case 2:
						tempCell = new Cell(TOP, cellTextures[TOP]);
						break;
					case 3:
						tempCell = new Cell(TRCCCORNER,
								cellTextures[TRCCCORNER]);
					}
					break;

				case 0:
					switch (j) {
					case 0:
						tempCell = new Cell(BLCCCORNER,
								cellTextures[BLCCCORNER]);
						break;
					case 1:
					case 2:
						tempCell = new Cell(BOTTOM, cellTextures[BOTTOM]);
						break;
					case 3:
						tempCell = new Cell(BRCCCORNER,
								cellTextures[BRCCCORNER]);
					}
					break;
				}
				tempCell->id = count;
				tempCell->left = (0 + j * cellsize);
				tempCell->right = (cellsize + j * cellsize);
				tempCell->bottom = (0 + i * cellsize);
				tempCell->top = (cellsize + i * cellsize);
				cellList->push_back(tempCell);
				count++;
			}
		}
		loc.x = 700;
		loc.y = 300;
		player->setLocation(loc);
		enemies->push_back(new Enemy(1));
		friendlies->push_back(new Friendly(1));
		loc.x = 750;
		loc.y = 1000;
		whirlpool->setLocation(loc);
		player->setwpLoc(whirlpool->getLocation());
		break;
	}
}

Level* Level::getLevelHandle() {
	return (Level*) level;
}

void Level::setCurrentActorCell(Actor* a) {
	Coordinate loc = a->getLocation();
	Cell* c;
	for (vector<Cell*>::iterator it = Level::cellList->begin(); it
			!= Level::cellList->end(); ++it) {
		c = *it;
		if ((loc.x < c->right) && (loc.x >= c->left) && (loc.y < c->top)
				&& (loc.y >= c->bottom)) {
			int aCell = a->getCurrentCellId();
			if (aCell != -1) {
				Level::cellList->at(aCell)->unregisterActor(a);
			}
			a->setCurrentCell(c->id);
			c->registerActor(a);
		}
	}
}

void Level::loadTextures() {
	int numtextures = 14;
	GLuint* texture = new GLuint[numtextures];
	// allocate a texture name
	glGenTextures(numtextures, texture);
	cellTextures[OPEN] = texture[0];
	loadImage("open.raw", cellTextures[OPEN]);
	cellTextures[FULL] = texture[1];
	loadImage("full.raw", cellTextures[FULL]);
	cellTextures[TLCCCORNER] = texture[2];
	loadImage("tlcccorner.raw", cellTextures[TLCCCORNER]);
	cellTextures[TRCCCORNER] = texture[3];
	loadImage("trcccorner.raw", cellTextures[TRCCCORNER]);
	cellTextures[BLCCCORNER] = texture[4];
	loadImage("blcccorner.raw", cellTextures[BLCCCORNER]);
	cellTextures[BRCCCORNER] = texture[5];
	loadImage("brcccorner.raw", cellTextures[BRCCCORNER]);
	cellTextures[TLCVCORNER] = texture[6];
	loadImage("tlcvcorner.raw", cellTextures[TLCVCORNER]);
	cellTextures[TRCVCORNER] = texture[7];
	loadImage("trcvcorner.raw", cellTextures[TRCVCORNER]);
	cellTextures[BLCVCORNER] = texture[8];
	loadImage("blcvcorner.raw", cellTextures[BLCVCORNER]);
	cellTextures[BRCVCORNER] = texture[9];
	loadImage("brcvcorner.raw", cellTextures[BRCVCORNER]);
	cellTextures[LEFT] = texture[10];
	loadImage("left.raw", cellTextures[LEFT]);
	cellTextures[RIGHT] = texture[11];
	loadImage("right.raw", cellTextures[RIGHT]);
	cellTextures[BOTTOM] = texture[12];
	loadImage("bottom.raw", cellTextures[BOTTOM]);
	cellTextures[TOP] = texture[13];
	loadImage("top.raw", cellTextures[TOP]);
	delete[] texture;
}

void Level::unloadTextures() {
	map<cellType, GLuint>::iterator it;
	for (it = cellTextures.begin(); it != cellTextures.end(); ++it) {
		glDeleteTextures(1, (GLuint*) &((*it).second));
	}
}

bool Level::loadImage(string filename, GLuint& texture) {
	int width, height;
	FILE * fp;
	string fname = "textures/";
	fname.append(filename);

	// texture data
	width = 256;
	height = 256;

	// open and read texture data
	fp = fopen(fname.c_str(), "rb");
	if (fp == NULL) {
		return false;
	}
	unsigned char *image = new unsigned char[width * height * 4];
	unsigned char r, g, b, a;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			r = getc(fp);
			g = getc(fp);
			b = getc(fp);
			a = getc(fp);

			image[i * width * 4 + j * 4] = r;
			image[i * width * 4 + j * 4 + 1] = g;
			image[i * width * 4 + j * 4 + 2] = b;
			image[i * width * 4 + j * 4 + 3] = a;

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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image);

	delete[] image; // free image data (no longer used)
	//return texture;
	return true;
}

void Level::killActor(Actor* a) {
	vector<Actor*>::iterator it;
	actorType at = a->getType();
	Cell* c = Level::cellList->at(a->getCurrentCellId());
	Friendly* f;
	Enemy* e;
	switch (at) {
	case ENEMY:
		for (it = this->enemies->begin(); it != this->enemies->end(); ++it) {
			if ((*it)->getId() == a->getId()) {
				enemies->erase(it);
				break;
			}
		}
		f = new Friendly(a);
		friendlies->push_back(f);
		c->registerActor(f);
		break;
	case FRIENDLY:
		for (it = this->friendlies->begin(); it != this->friendlies->end(); ++it) {
			if ((*it)->getId() == a->getId()) {
				friendlies->erase(it);
				break;
			}
		}
		e = new Enemy(a);
		enemies->push_back(e);
		c->registerActor(e);
		break;
	default:
		break;
	}
}
