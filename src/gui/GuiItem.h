#pragma once

#include "../IRender2d.h"
#include <vector>

class GuiItem
{

public:
	

	std::vector<GuiItem*> m_childs;
	GuiItem* m_parent;
	bool m_clickIsOn;
	bool m_mouseLast;

	int m_x, m_y, m_width, m_height;
	int globalX, globalY;

	GuiItem(int x, int y, int width, int height);

	virtual void draw(IRender2d* ctx);

	virtual void mouseOn(IRender2d* ctx);
	virtual void mouseOnClick(IRender2d* ctx);
	virtual void mouseDefault(IRender2d* ctx);
	virtual void activated();

	bool isMouseOn();

	void addChild(GuiItem* item);
	void calculateGlobalPos();

};