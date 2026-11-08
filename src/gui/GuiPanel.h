#pragma once

#include "GuiItem.h"

class GuiPanel : public GuiItem
{

public:

	unsigned char m_r, m_g, m_b;

	GuiPanel(int x, int y, int width, int height);

	virtual void draw(IRender2d* ctx);

};