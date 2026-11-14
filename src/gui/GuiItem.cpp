#include "GuiItem.h"
#include "../Input.h"

extern Input input;

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

bool GuiItem::mouseOn()
{
	return input.m_mouseX > m_x && input.m_mouseY > m_y &&
		input.m_mouseX < m_x + m_width && input.m_mouseY < m_y + m_height;
}