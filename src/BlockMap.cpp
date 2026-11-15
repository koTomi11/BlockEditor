#include "BlockMap.h"

BlockMap::BlockMap()
{
	m_bitmap = new BlockId[64 * 64];
	memset(m_bitmap, 0, 64 * 64 * sizeof(BlockId));
}

bool BlockMap::isBlock(int x, int y, int layer)
{
	return getBlockId(x,y,layer).objType != 0;
}

BlockId BlockMap::getBlockId(int x, int y, int layer)
{
	return m_bitmap[y * 64 + x];
}