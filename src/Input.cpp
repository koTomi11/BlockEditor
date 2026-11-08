#include "Input.h"

void Input::clearTypedText()
{
	m_typedText.clear();
}

std::string Input::getText()
{
	return m_typedText;
}

bool Input::isMouseLeftClick()
{
	return mouseButton[0];
}

bool Input::isMouseRightClick()
{
	return mouseButton[1];
}

bool Input::isMouseScroolClick()
{
	return mouseButton[2];
}