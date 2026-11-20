#pragma once

#include "GuiButton.h"
#include "GuiPanel.h"

class GuiMenuBar : public GuiPanel
{

public:

	GuiMenuBar(int width) : GuiPanel(0, 0, width, 30) {}

	void draw(IRender2d* ctx) override;

	void addMenu(std::string str);

};