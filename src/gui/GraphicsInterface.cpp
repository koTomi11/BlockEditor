#include "GraphicsInterface.h"

#include <iostream>

#include "GuiPanel.h"

int xx = 0;

GraphicsInterface::GraphicsInterface()
{
	p = new GuiPanel(200, 200, 300, 300);
}

void GraphicsInterface::mouseMove(int x, int y)
{
	std::cout << x << std::endl;

	xx = x;
}

void GraphicsInterface::draw(IRender2d* ctx)
{

	p->draw(ctx);


}