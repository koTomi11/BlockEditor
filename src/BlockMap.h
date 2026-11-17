#pragma once

#include <vector>
#include <string>

struct attrib
{
	std::string key, value; 
};

struct BlockId
{
	unsigned short objType : 4;
	unsigned short objIndex : 12;
};

class Entity
{

public:

	int m_x, m_y, m_layout;
	float m_offsetX, m_offsetY, m_offsetZ;
	std::vector<attrib> m_attribs;

	Entity(int x, int y, int layout)
	{
		m_x = x; m_y = y; m_layout = layout;
	}

};

struct Block
{
	int m_x, m_y;
	BlockId m_next, m_prev;
};

struct Solid : Block
{
	enum { ID = 1 };

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
	enum {ID = 4};
};


class BlockMap
{

public:

	BlockId* m_bitmap;
	std::vector<Solid> m_solids;
	std::vector<CeilFloor> m_cf;
	std::vector<Port> m_ports;
	std::vector<Empty> m_emptys;
	
	std::vector<Entity> m_entityes;

	BlockMap();

	bool isBlock(int x, int y, int layer);
	BlockId getBlockId(int x, int y, int layer);

	Block& getBaseObject(BlockId id);
	
	void addToBitmap(int x, int y, int layer, BlockId id);
	
	void newBlock(int x, int y, int layer, Solid s)
	{
		BlockId id;
		id.objIndex = m_solids.size();
		id.objType = Solid::ID;
		addToBitmap(x, y, layer, id);

		s.m_x = x;
		s.m_y = y;
		m_solids.push_back(s);
		
		
	}

	void newBlock(int x, int y, int layer, CeilFloor s)
	{
		BlockId id;
		id.objIndex = m_cf.size();
		id.objType = CeilFloor::ID;
		addToBitmap(x, y, layer, id);
		s.m_x = x;
		s.m_y = y;
		m_cf.push_back(s);
	}

	void newBlock(int x, int y, int layer, Port s)
	{
		BlockId id;
		id.objIndex = m_ports.size();
		id.objType = Port::ID;
		addToBitmap(x, y, layer, id);
		s.m_x = x;
		s.m_y = y;
		m_ports.push_back(s);
	}

	void newBlock(int x, int y, int layer, Empty s)
	{
		BlockId id;
		id.objIndex = m_emptys.size();
		id.objType = Empty::ID;
		addToBitmap(x, y, layer, id);
		s.m_x = x;
		s.m_y = y;
		m_emptys.push_back(s);
	}

};