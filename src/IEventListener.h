#pragma once

class IEventListener
{

public:

	virtual void mouseMove(int x, int y) {}
	virtual void mouseButton(int code){}
	virtual void keyPress(int keycode) {}
	virtual void keyType(char c) {}

};