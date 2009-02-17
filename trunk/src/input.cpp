#include "input.hpp"

void* Input::input;
std::queue<Input::keyPress*>* Input::keyBuffer;

Input::Input()	{
	keyBuffer = new std::queue<keyPress*>();
	this->input = (void*) this;
}

Input::~Input()	{
	delete this->keyBuffer;
}

void Input::processKeysWrapper(unsigned char key, int x, int y)	{
	Input* i = (Input*) Input::input;
	i->processKeys(key, x, y);
}

void Input::processKeys(unsigned char key, int x, int y)	{
	keyPress* k = new keyPress();
	k->nKey = key;
	k->sKey = -1;
	k->x = x;
	k->y = y;
	k->pressed = true;
	this->pushKey(k);
}

void Input::processSpecialKeysWrapper(int key, int x, int y)	{
	Input* i = (Input*) Input::input;
	i->processSpecialKeys(key, x, y);
}

void Input::processSpecialKeys(int key, int x, int y)	{
	keyPress* k = new keyPress();
	k->nKey = -1;
	k->sKey = key;
	k->x = x;
	k->y = y;
	k->pressed = true;
	this->pushKey(k);
}

void Input::processKeysReleasedWrapper(unsigned char key, int x, int y)	{
	Input* i = (Input*) Input::input;
	i->processKeysReleased(key, x, y);
}

void Input::processKeysReleased(unsigned char key, int x, int y)	{
	keyPress* k = new keyPress();
	k->nKey = key;
	k->sKey = -1;
	k->x = x;
	k->y = y;
	k->pressed = false;
	this->pushKey(k);
}

void Input::processSpecialKeysReleasedWrapper(int key, int x, int y)	{
	Input* i = (Input*) Input::input;
	i->processSpecialKeysReleased(key, x, y);
}

void Input::processSpecialKeysReleased(int key, int x, int y)	{
	keyPress* k = new keyPress();
	k->nKey = -1;
	k->sKey = key;
	k->x = x;
	k->y = y;
	k->pressed = false;
	this->pushKey(k);
}

void Input::pushKey(keyPress* k)	{
	Input::keyBuffer->push(k);
}

Input::keyPress* Input::popKey()	{
	keyPress* k = Input::keyBuffer->front();
	Input::keyBuffer->pop();
	return k;
}

bool Input::checkKeyBuffer()	{
	return !(Input::keyBuffer->empty());
}
