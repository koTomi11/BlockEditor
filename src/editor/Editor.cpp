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

	addChild(new GuiButton(10,20,"layer+",Btns_SET_LAYER_P, this));
	addChild(new GuiButton(10, 60, "layer-", Btns_SET_LAYER_N, this));

	addChild(new GuiButton(10, 100, "Solid", Btns_SET_SOLID, this));
	addChild(new GuiButton(10, 140, "CeilFloor", Btns_SET_CEILFLOOR, this));
	addChild(new GuiButton(10, 180, "Port", Btns_SET_PORT, this));

	addChild(new GuiButton(10, 260, "player", Btns_PLAYER, this));
	addChild(new GuiButton(10, 300, "zombie", Btns_ZOMBIE, this));
	addChild(new GuiButton(10, 340, "soldier", Btns_SOLDIER, this));
	addChild(new GuiButton(10, 380, "headcrab", Btns_HEADCRAB, this));

	
	

}

void Editor::update(IRender2d* ctx)
{
	GuiPanel::draw(ctx);
	ctx->drawString(200, 50, std::to_string(m_currentLayer));


	m_grid->draw(ctx);
	
	
}

void Editor::save(std::string fileName)
{
	MapGenerator g;
	g.generate(m_blockMap).save(fileName);
}

void Editor::onClick(int x, int y)
{



	if (m_currentBlock == 100)
	{
		bool v = true;
		for (Entity e : m_blockMap->m_entityes)
		{
			if (e.m_x == x && e.m_y == y)
			{
				v = false;
			}
		}

		if (v)
		{
			Entity e(x, y, m_currentLayer);
			e.m_type = m_currentEntity;
			m_blockMap->m_entityes.push_back(e);

		}
	}


	if (!m_blockMap->isBlock(x, y, m_currentLayer))
	{

			Port p, p2;

			switch (m_currentBlock)
			{
			case Solid::ID: m_blockMap->newBlock(x, y, m_currentLayer, Solid()); break;
			case CeilFloor::ID: m_blockMap->newBlock(x, y, m_currentLayer, CeilFloor()); break;
			case Port::ID: 
				m_blockMap->newBlock(x, y, m_currentLayer, p2);
				p.m_up = false;
				p2.m_up = true;
				m_blockMap->newBlock(x, y, m_currentLayer + 1, p);
			
				break;

		
					
			}
		}
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


	for (Entity e : m_blockMap->m_entityes)
	{
		if (m_currentLayer == e.m_layer)
		{
			if (e.m_type.compare("info_player_start") == 0)
			{
				ctx->setColor(10, 10, 200);
			}
			else if (e.m_type.compare("monster_human_grunt") == 0)
			{
				ctx->setColor(200, 10, 10);
			}
			else if (e.m_type.compare("monster_zombie") == 0)
			{
				ctx->setColor(200, 100, 10);
			}
			else if (e.m_type.compare("monster_headcrab") == 0)
			{
				ctx->setColor(100, 100, 10);
			}

			ctx->fillCircle(m_gridSize * e.m_x + 10, m_gridSize * e.m_y + 10, 10);
		}
	}

}


void Editor::buttonDown(int i)
{

	m_currentEntity.clear();
	switch (i)
	{

	case Btns_SET_LAYER_N: m_currentLayer--; break;
	case Btns_SET_LAYER_P: m_currentLayer++; break;
	case Btns_SET_SOLID: m_currentBlock = Solid::ID; break;
	case Btns_SET_CEILFLOOR: m_currentBlock = CeilFloor::ID; break;
	case Btns_SET_PORT: m_currentBlock = Port::ID; break;
	
	case Btns_PLAYER: m_currentEntity = "info_player_start";  m_currentBlock = 100; break;
	case Btns_ZOMBIE: m_currentEntity = "monster_zombie"; m_currentBlock = 100; break;
	case Btns_HEADCRAB: m_currentEntity = "monster_headcrab"; m_currentBlock = 100; break;
	case Btns_SOLDIER: m_currentEntity = "monster_human_grunt"; m_currentBlock = 100; break;

	}
}