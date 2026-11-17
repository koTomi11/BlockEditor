#include "GuiItem.h"
#include "../Input.h"

#include <iostream>

extern Input input;

GuiItem::GuiItem(int x, int y, int width, int height)
{
	m_x = x; m_y = y; m_width = width; m_height = height;
	m_parent = nullptr;
	m_clickIsOn = false;
}

void GuiItem::draw(IRender2d* ctx)
{
	calculateGlobalPos();
	for (GuiItem* item : m_childs)
		item->draw(ctx);

	ctx->setPos(globalX, globalY);
	if (isMouseOn())
	{
		if (input.isMouseLeftClick())
		{
			if (!m_mouseLast)
			{
				m_clickIsOn = true;
			}
			else
			{
				mouseDefault(ctx);
			}
		}
		else
		{
			mouseOn(ctx);
			if (m_clickIsOn)
			{
				activated();
			}
		}
	}
	else
	{
		mouseDefault(ctx);
	}

	if (!input.isMouseLeftClick())
	{
		m_clickIsOn = false;
	}

	if (m_clickIsOn)
	{
		mouseOnClick(ctx);
	}

	m_mouseLast = input.isMouseLeftClick();
}

void GuiItem::activated()
{
	
}

bool GuiItem::isMouseOn()
{
	return input.m_mouseX > globalX && input.m_mouseY > globalY &&
		input.m_mouseX < globalX + m_width && input.m_mouseY < globalY + m_height;
}

void GuiItem::mouseOn(IRender2d* ctx)
{

}

void GuiItem::mouseOnClick(IRender2d* ctx)
{

}

void GuiItem::mouseDefault(IRender2d* ctx)
{

}

void GuiItem::addChild(GuiItem* item)
{
	item->m_parent = this;
	m_childs.push_back(item);
}

void GuiItem::calculateGlobalPos()
{
	globalX = m_x; globalY = m_y;

	GuiItem* item = m_parent;
	while (item != nullptr)
	{
		globalX += item->m_x;
		globalY += item->m_y;

		item = item->m_parent;
	}
}