#include "GuiItem.h"

GuiItem::GuiItem(int x, int y, int width, int height)
{
	m_x = x; m_y = y; m_width = width; m_height = height;
}

void GuiItem::draw(IRender2d* ctx)
{
	ctx->setPos(m_x, m_y);

	for (GuiItem* item : m_childs)
		item->draw(ctx);
}