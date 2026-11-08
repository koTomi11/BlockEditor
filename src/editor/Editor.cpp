#include "Editor.h"

#include <memory>
#include "../Input.h"
#include <iostream>


extern Input input;

Editor::Editor() : GuiPanel(0, 0, 800, 600)
{

	m_bitmap = new BlockId[64 * 64];
	memset(m_bitmap, 0, 64 * 64 * sizeof(BlockId));

	m_gridSize = 20;
	
}

void Editor::update(IRender2d* ctx, int mX, int mY, bool click)
{
	GuiPanel::draw(ctx);

	if (input.isMouseLeftClick())
	{

		int x = input.m_mouseX / m_gridSize;
		int y = input.m_mouseY / m_gridSize;
		
		if(!isBlock(x,y))
			addBlock(x, y, Block());
	


	}

	ctx->setColor(40, 40, 40);
	ctx->setLineWidth(2);

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine(0, i * m_gridSize, 800, i * m_gridSize);
	}

	for (int i = 0; i < 64; i++)
	{
		ctx->drawLine( i * m_gridSize,0,  i * m_gridSize, 600);
	}

	ctx->setColor(100, 100, 200);

	for (Block b : m_blocks)
	{
		//ctx->fillCircle(b.m_x + m_gridSize / 2, b.m_y + m_gridSize / 2, m_gridSize);

		ctx->fillRect(b.m_x * m_gridSize, b.m_y * m_gridSize, m_gridSize, m_gridSize);
	}

}

bool Editor::isBlock(int x, int y)
{
	for (Block b : m_blocks)
		if (b.m_x == x && b.m_y == y) return true;

	return false;
}

void Editor::addBlock(int x, int y, Block block)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = 1;
	m_bitmap[index].objIndex = m_blocks.size();
	block.m_x = x;
	block.m_y = y;
	m_blocks.push_back(block);

}

void Editor::save(std::string fileName)
{

	MapBuilder map;

	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			if (m_bitmap[y * 64 + x].objType != 0)
			{
				Block b = m_blocks[m_bitmap[y * 64 + x].objIndex];

				map.addBlock(x * 100, y * 100);

			}
			
		}
	}

	map.save(fileName);

}