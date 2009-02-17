#ifndef __INPUT_HPP__
#define __INPUT_HPP__
#include <queue>

class Input	{
public:
	typedef struct	{
		unsigned char nKey;
		int sKey;
		int x;
		int y;
		bool pressed;
	} keyPress;

	Input();
	~Input();
	static Input::keyPress* popKey();
	static bool checkKeyBuffer();
	static void processKeysWrapper(unsigned char key, int x, int y);
	static void processSpecialKeysWrapper(int key, int x, int y);
	static void processKeysReleasedWrapper(unsigned char key, int x, int y);
	static void processSpecialKeysReleasedWrapper(int key, int x, int y);
	//processMouse(int button, int state, int x, int y);
	//pushMouse();
	//popMouse();
	//checkMouseBuffer();
	//pushJoystick();
	//popJoystick();
	//checkJoystickBuffer();

private:
	static void* input;
	void processKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int x, int y);
	void processKeysReleased(unsigned char key, int x, int y);
	void processSpecialKeysReleased(int key, int x, int y);
	void pushKey(keyPress*);
	static std::queue<keyPress*>* keyBuffer;
};

#endif //__INPUT_HPP__
