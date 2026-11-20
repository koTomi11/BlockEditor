#include "GuiButton.h"


GuiButton::GuiButton(int x, int y, std::string label, int id, IButtonListener* listener) : GuiItem(x, y, 100, 30)
{
	m_listener = listener;
	m_label = label;
	m_id = id;
}


void GuiButton::draw(IRender2d* ctx)
{
	GuiItem::draw(ctx);

	ctx->setColor(20, 20, 20);
	ctx->drawString(0, 18, m_label);

}

void GuiButton::activated()
{
	m_listener->buttonDown(m_id);
}

void GuiButton::mouseOn(IRender2d* ctx)
{
	ctx->setColor(46, 50, 62);
	ctx->fillRect(0, 0, 100, 30);
}

void GuiButton::mouseOnClick(IRender2d* ctx)
{
	ctx->setColor(59, 130, 246);
	ctx->fillRect(0, 0, 100, 30);
}

void GuiButton::mouseDefault(IRender2d* ctx)
{
	ctx->setColor(50, 100, 100);
	ctx->fillRect(0, 0, 100, 30);
}