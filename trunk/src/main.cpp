#include "includes.hpp"
#include "game.hpp"

void init()	{
	//register callbacks like glutDisplayFunc() etc...
	glutDisplayFunc(&Game::displayWrapper);
	glutIdleFunc(&Game::displayWrapper);
	glutKeyboardFunc(&Input::processKeysWrapper);
	glutSpecialFunc(&Input::processSpecialKeysWrapper);
	glutKeyboardUpFunc(&Input::processKeysReleasedWrapper);
	glutSpecialUpFunc(&Input::processSpecialKeysReleasedWrapper);
	return;
}

int main (int argc, char** argv)	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Fish rescue");
	glutFullScreen();

	//Set screen mode at 800x600 w/ 32bit colour
	//TODO: make this changeable with an option menu
	//std::string modeString;
	//std::ostringstream stm;

	/*glutGameModeString("1024x768:24");
	// enter full screen
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
		glutEnterGameMode();
	}
	else {
		printf("The selected mode is not available\n");
		exit(1);
	}
	glutEnterGameMode();
	*/
	Game* game = new Game();
	game->setMode(1024,768);
	/*game->setMode(glutGameModeGet(GLUT_GAME_MODE_WIDTH), glutGameModeGet(GLUT_GAME_MODE_HEIGHT));
	stm << "Current Mode: Game Mode " << game->getScreenHeight()
		<< "x" << game->getScreenWidth()
		<< " at " << glutGameModeGet(GLUT_GAME_MODE_REFRESH_RATE)
		<< " hertz, " << glutGameModeGet(GLUT_GAME_MODE_PIXEL_DEPTH) << " bpp";
	modeString = stm.str();
	std::cout << modeString << std::endl;
	*/
	// register all callbacks and
	// create display lists
	init();

	glutMainLoop();

	return(0);
}
