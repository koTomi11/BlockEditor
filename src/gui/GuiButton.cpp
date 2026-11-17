#include "GuiButton.h"

void GuiButton::draw(IRender2d* ctx)
{
	GuiItem::draw(ctx);

	ctx->drawString(10, 50, std::to_string(c));

}

void GuiButton::activated()
{
	c++;
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