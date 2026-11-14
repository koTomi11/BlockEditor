#include "Editor.h"

#include <memory>
#include "../Input.h"
#include <iostream>

#include <GLFW/glfw3.h>

extern Input input;

Editor::Editor(int x, int y, int width, int height) : GuiPanel(x, y, width, height)
{

	m_bitmap = new BlockId[64 * 64];
	memset(m_bitmap, 0, 64 * 64 * sizeof(BlockId));

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
		
		if (!isBlock(x, y))
			newSolid(x, y);
	}

	if (input.currentKeyDown[GLFW_KEY_P] && mouseOn())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;

		if (!isBlock(x, y))
			newPort(x, y);
	}

	if (input.isMouseRightClick() && mouseOn())
	{
		int x = (input.m_mouseX - m_x) / m_gridSize;
		int y = (input.m_mouseY - m_y) / m_gridSize;

		if (!isBlock(x, y))
			newCeilFloor(x, y);
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
			BlockId id = m_bitmap[i * 64 + j];

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

bool Editor::isBlock(int x, int y)
{
	return  m_bitmap[y * 64 + x].objType != 0;
}

BlockId Editor::getBlockId(int x, int y)
{

	BlockId id = m_bitmap[y * 64 + x];

	return id;
}

void Editor::addBlock(int x, int y, Solid block)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = Port::ID;
	m_bitmap[index].objIndex = m_solids.size();
	block.m_x = x;
	block.m_y = y;
	m_solids.push_back(block);

}

void Editor::save(std::string fileName)
{

	MapBuilder map;

	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{

			BlockId id = m_bitmap[y * 64 + x];
			int blockX = x * 100;
			int blockY = y * 100;

			switch (id.objType)
			{

			case Solid::ID:
				map.addBlock(blockX, blockY, 0);
				break;


			case CeilFloor::ID:
				map.addBlock(blockX, blockY, 100);
				map.addBlock(blockX, blockY, -100);
				break;

			case Port::ID:

				Port p = m_ports[id.objIndex];

				if (p.m_up)
				{
					map.addBlock(blockX + 100, blockY, 200);
					map.addBlock(blockX - 100, blockY, 200);
					map.addBlock(blockX, blockY + 100, 200);
					map.addBlock(blockX, blockY - 100, 200);
					map.addBlock(blockX, blockY, -100);
				}
				else
				{
					map.addBlock(blockX + 100, blockY, -200);
					map.addBlock(blockX - 100, blockY, -200);
					map.addBlock(blockX, blockY + 100, -200);
					map.addBlock(blockX, blockY - 100, -200);
					map.addBlock(blockX, blockY, 100);
				}

				break;

			}
		}
	}

	map.save(fileName);

}

void Editor::newSolid(int x, int y)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = Solid::ID;
	m_bitmap[index].objIndex = m_solids.size();
	m_solids.push_back(Solid());

}

void Editor::newCeilFloor(int x, int y)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = CeilFloor::ID;
	m_bitmap[index].objIndex = m_cf.size();
	m_cf.push_back(CeilFloor());
}

void Editor::newPort(int x, int y)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = Port::ID;
	m_bitmap[index].objIndex = m_ports.size();

	Port p;
	p.m_up = true;
	m_ports.push_back(p);
}