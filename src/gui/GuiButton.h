#pragma once

#include "GuiItem.h"

class GuiButton : public GuiItem
{

public:

	int c;

	GuiButton(int x, int y) : GuiItem(x, y, 100, 30) { c = 0; }

	void draw(IRender2d* ctx) override;

	virtual void activated() override;
	virtual void mouseOn(IRender2d* ctx) override;
	virtual void mouseOnClick(IRender2d* ctx) override;
	virtual void mouseDefault(IRender2d* ctx) override;
	
};