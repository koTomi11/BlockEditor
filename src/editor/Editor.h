#pragma once


#include "../map_builder/MapBuilder.h"

#include "../IRender2d.h"

#include "../gui/GuiPanel.h"

class Block
{

public:

	int m_x, m_y;

};

struct BlockId
{
	unsigned short objType : 4;
	unsigned short objIndex : 12;
};

class Editor : public GuiPanel
{

public:

	BlockId* m_bitmap;
	std::vector<Block> m_blocks;

	int m_gridSize;

	Editor();

	void addBlock(int x, int y, Block block);
	void update(IRender2d* ctx, int mX, int mY, bool click);
	bool isBlock(int x, int y);
	void save(std::string fileName);

};