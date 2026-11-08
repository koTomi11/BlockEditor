#pragma once

#include "../IRender2d.h"
#include <vector>

class GuiItem
{

public:

	std::vector<GuiItem*> m_childs;

	int m_x, m_y, m_width, m_height;

	GuiItem(int x, int y, int width, int height);

	virtual void draw(IRender2d* ctx);


};