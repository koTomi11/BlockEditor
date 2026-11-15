#include "Editor.h"

#include <memory>
#include "../Input.h"
#include <iostream>
#include "../MapGenerator.h"
#include <GLFW/glfw3.h>

extern Input input;

Editor::Editor(int x, int y, int width, int height) : GuiPanel(x, y, width, height)
{

	m_blockMap = new BlockMap();

	m_gridSize = 20;

	m_currentLayer = 0;
	m_currentBlock = 1;
	
}

void Editor::update(IRender2d* ctx)
{
	GuiPanel::draw(ctx);

	if (input.isMouseLeftClick() && mouseOn())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;
		
		if (!m_blockMap->isBlock(x, y,0))
			m_blockMap->newBlock(x, y, 0, Solid());
	}

	if (input.currentKeyDown[GLFW_KEY_P] && mouseOn())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;

		if (!m_blockMap->isBlock(x, y, 0))
			m_blockMap->newBlock(x, y, 0, Port());
	}

	if (input.isMouseRightClick() && mouseOn())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;

		if (!m_blockMap->isBlock(x, y, 0))
			m_blockMap->newBlock(x, y, 0, CeilFloor());
	}

	if (input.currentKeyDown[GLFW_KEY_0])
	{
		m_currentLayer = 0;
	}

	if (input.currentKeyDown[GLFW_KEY_1])
	{
		m_currentLayer = 1;
	}


	ctx->setColor(40, 40, 40);
	ctx->setLineWidth(2);

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine(0, i * m_gridSize, m_width, i * m_gridSize);
	}

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine( i * m_gridSize,0,  i * m_gridSize, m_height);
	}

	ctx->setColor(100, 100, 200);

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			
			BlockId id = m_blockMap->getBlockId(j, i, 0);

			switch (id.objType)
			{

				case Solid::ID: ctx->setColor(50,50,50); 
					ctx->fillRect(j * m_gridSize, i * m_gridSize, m_gridSize, m_gridSize);
					break;
				case CeilFloor::ID: ctx->setColor(200, 200, 200);
					ctx->fillRect(j * m_gridSize, i * m_gridSize, m_gridSize, m_gridSize); 
					break;
				case Port::ID: ctx->setColor(50, 50, 200);
					ctx->fillRect(j * m_gridSize, i * m_gridSize, m_gridSize, m_gridSize);
					break;

			}
		}
	}
}

void Editor::save(std::string fileName)
{
	MapGenerator g;
	g.generate(m_blockMap).save(fileName);
}
