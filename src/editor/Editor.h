#pragma once


#include "../map_builder/MapBuilder.h"

class Block
{

public:



};

struct BlockId
{
	unsigned short objType : 4;
	unsigned short objIndex : 12;
};

class Editor
{

public:

	BlockId* m_bitmap;
	std::vector<Block> m_blocks;

	Editor();

	void addBlock(int x, int y, Block block);

	void save(std::string fileName);

};