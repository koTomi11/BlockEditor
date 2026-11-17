#include "GuiPanel.h"

GuiPanel::GuiPanel(int x, int y, int width, int height) : GuiItem(x, y, width, height)
{
	m_r = 30; m_g = 32; m_b = 40; 
}

 void GuiPanel::draw(IRender2d* ctx)
{
	 GuiItem::draw(ctx);
	
	 
	

	 /*
	 ctx->setColor(50, 50, 50);
	 ctx->fillRect(0, -30, m_width, 30);
	 ctx->setColor(0, 0, 0);
	

	 ctx->setColor(10, 10, 10);
	 ctx->setLineWidth(1);
	 ctx->drawRect(0, -30, m_width, 30);
	 ctx->drawRect(0, 0, m_width, m_height);
	 */
}