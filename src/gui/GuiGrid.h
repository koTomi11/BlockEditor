#pragma once

#include "GuiPanel.h"

class IGridInterface
{

public:

	virtual void onClick(int x, int y) = 0;
	virtual void draw(IRender2d* ctx, int x, int y, int width, int height) = 0;

};

class GuiGrid : public GuiPanel
{

public:

	int m_gridSize;
	int m_gridX, m_gridY, m_gridW, m_gridH;
	IGridInterface* m_gridInterface;

	GuiGrid(IGridInterface* gridInterface, int x, int y, int width, int height);
	
	void draw(IRender2d* ctx) override;
	
};