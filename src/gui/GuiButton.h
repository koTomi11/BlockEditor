#pragma once

#include "GuiItem.h"

class IButtonListener
{
public:

	virtual void buttonDown(int id) = 0;

};

class GuiButton : public GuiItem
{

public:

	int c;
	IButtonListener* m_listener;
	std::string m_label;
	int m_id;

	GuiButton(int x, int y) : GuiItem(x, y, 100, 30) { c = 0; }
	GuiButton(int x, int y, std::string label, int id, IButtonListener* listener);

	void draw(IRender2d* ctx) override;

	virtual void activated() override;
	virtual void mouseOn(IRender2d* ctx) override;
	virtual void mouseOnClick(IRender2d* ctx) override;
	virtual void mouseDefault(IRender2d* ctx) override;
	
};