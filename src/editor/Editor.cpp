#include "Editor.h"

#include <memory>
#include "../Input.h"
#include <iostream>
#include "../MapGenerator.h"
#include <GLFW/glfw3.h>

#include "../gui/GuiButton.h"

extern Input input;

Editor::Editor(int x, int y, int width, int height) : GuiPanel(x, y, width, height)
{

	m_blockMap = new BlockMap();

	m_gridSize = 20;

	m_currentLayer = 0;
	m_currentBlock = 1;
	
	m_grid = new GuiGrid(this, 300, 30, width - 300, height - 80);
	m_grid->m_gridSize = 20;

	addChild(new GuiButton(10, 10));

}

void Editor::update(IRender2d* ctx)
{
	GuiPanel::draw(ctx);
	m_grid->draw(ctx);
	
	
}

void Editor::save(std::string fileName)
{
	MapGenerator g;
	g.generate(m_blockMap).save(fileName);
}

void Editor::onClick(int x, int y)
{
	if (!m_blockMap->isBlock(x, y, m_currentLayer))
		m_blockMap->newBlock(x, y, m_currentLayer, Solid());
}

void Editor::draw(IRender2d* ctx, int x, int y, int width, int height)
{
	ctx->setColor(100, 100, 200);

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{

			BlockId id = m_blockMap->getBlockId(j, i, m_currentLayer);

			switch (id.objType)
			{

			case Solid::ID: ctx->setColor(50, 50, 50);
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
