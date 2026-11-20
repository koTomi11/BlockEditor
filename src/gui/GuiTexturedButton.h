#pragma once

#include "GuiButton.h"


class GuiTexturedButton : public GuiButton
{

public:

	int m_texture;

	GuiTexturedButton(int x, int y, int texture, int id, IButtonListener* listener);

	virtual void mouseOn(IRender2d* ctx) override;
	virtual void mouseOnClick(IRender2d* ctx) override;
	virtual void mouseDefault(IRender2d* ctx) override;

};