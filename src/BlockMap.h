#pragma once

#include <vector>

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

	BlockMap();

	bool isBlock(int x, int y, int layer);
	BlockId getBlockId(int x, int y, int layer);
	
	
	void newBlock(int x, int y, int layer, Solid s)
	{
		int index = y * 64 + x;
		m_bitmap[index].objType = Solid::ID;
		m_bitmap[index].objIndex = m_solids.size();
		s.m_x = x;
		s.m_y = y;
		m_solids.push_back(s);
	}

	void newBlock(int x, int y, int layer, CeilFloor s)
	{
		int index = y * 64 + x;
		m_bitmap[index].objType = CeilFloor::ID;
		m_bitmap[index].objIndex = m_cf.size();
		s.m_x = x;
		s.m_y = y;
		m_cf.push_back(s);
	}

	void newBlock(int x, int y, int layer, Port s)
	{
		int index = y * 64 + x;
		m_bitmap[index].objType = Port::ID;
		m_bitmap[index].objIndex = m_ports.size();
		s.m_x = x;
		s.m_y = y;
		m_ports.push_back(s);
	}

	void newBlock(int x, int y, int layer, Empty s)
	{
		int index = y * 64 + x;
		m_bitmap[index].objType = Empty::ID;
		m_bitmap[index].objIndex = m_emptys.size();
		s.m_x = x;
		s.m_y = y;
		m_emptys.push_back(s);
	}

};