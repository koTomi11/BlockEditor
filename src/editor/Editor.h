#pragma once


#include "../map_builder/MapBuilder.h"

#include "../IRender2d.h"

#include "../gui/GuiPanel.h"

struct BlockId
{
	unsigned short objType : 4;
	unsigned short objIndex : 12;
};

struct Block
{
	int m_x, m_y;
	BlockId m_next, m_prev;
};

struct Solid : Block
{
	enum { ID = 1};

};

struct CeilFloor : Block
{
	enum { ID = 2 };
};

struct Port : Block
{
	enum { ID = 3 };
	bool m_up;
};

struct Empty : Block
{

};


class Editor : public GuiPanel
{

public:

	BlockId* m_bitmap;
	std::vector<Solid> m_solids;
	std::vector<CeilFloor> m_cf;
	std::vector<Port> m_ports;
	std::vector<Empty> m_emptys;

	int m_currentLayer;
	int m_currentBlock;

	int m_gridSize;

	Editor(int x, int y, int width, int height);

	void addBlock(int x, int y, Solid block);
	void update(IRender2d* ctx);
	bool isBlock(int x, int y);
	void save(std::string fileName);

	BlockId getBlockId(int x, int y);

	void newSolid(int x, int y);
	void newCeilFloor(int x, int y);
	void newPort(int x, int y);

};