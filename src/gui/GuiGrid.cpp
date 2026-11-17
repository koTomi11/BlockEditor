#include "GuiGrid.h"

#include "../Input.h"

extern Input input;

GuiGrid::GuiGrid(IGridInterface* gridInterface, int x, int y, int width, int height) : GuiPanel(x, y, width, height)
{
	m_gridInterface = gridInterface;
}

void GuiGrid::draw(IRender2d* ctx)
{
	GuiPanel::draw(ctx);

	ctx->setColor(40, 40, 40);
	ctx->setLineWidth(2);

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine(0, i * m_gridSize, m_width, i * m_gridSize);
	}

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine(i * m_gridSize, 0, i * m_gridSize, m_height);
	}


	if (isMouseOn() && input.isMouseLeftClick())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;

		m_gridInterface->onClick(x, y);

	}
	
	m_gridInterface->draw(ctx, 0, 0, m_width, m_height);
}