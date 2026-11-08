#pragma once

#include <string>

class Input
{

public:
	
	std::string m_typedText;
	int m_mouseX, m_mouseY;
	bool lastKeyDown[255];
	bool currentKeyDown[255];
	bool mouseButton[3];

	void clearTypedText();
	std::string getText();

	bool isMouseLeftClick();
	bool isMouseRightClick();
	bool isMouseScroolClick();

};