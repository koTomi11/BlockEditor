#include "GuiTexturedButton.h"


GuiTexturedButton::GuiTexturedButton(int x, int y, int texture, int id, IButtonListener* listener)
	: GuiButton(x, y, "", id, listener)
{
	m_texture = texture;
	m_width = 60;
	m_height = 60;
}


void GuiTexturedButton::mouseOn(IRender2d* ctx)
{
	ctx->drawImage(m_texture, 0, 0, m_width, m_height);
	ctx->setColor(0, 0, 0);
	ctx->drawRect(0, 0, m_width, m_height);
}

void GuiTexturedButton::mouseOnClick(IRender2d* ctx)
{

	ctx->drawImage(m_texture, 0, 0, m_width, m_height);
	ctx->setColor(50, 50, 50);
	ctx->drawRect(0, 0, m_width, m_height);
}

void GuiTexturedButton::mouseDefault(IRender2d* ctx)
{
	ctx->drawImage(m_texture, 0, 0, m_width, m_height);
}