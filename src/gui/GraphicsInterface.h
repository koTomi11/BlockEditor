#pragma once

#include "../IEventListener.h"
#include "../IRender2d.h"

#include "GuiPanel.h"

class GraphicsInterface : public IEventListener
{

public:

	GuiPanel* p;

	std::vector<GuiItem*> m_items;

	GraphicsInterface();

	void mouseMove(int x, int y) override;


	void draw(IRender2d* ctx);

};