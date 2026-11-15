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
	BlockId id = m_bitmap[y * 64 + x];

	if (layer < 0)
	{
		while (layer != 0)
		{
			id = getBaseObject(id).m_prev;
			layer++;
		}
	}
	else if(layer > 0){

		while (layer != 0)
		{
			id = getBaseObject(id).m_next;
			layer--;
		}
	}

	return id;
}

Block& BlockMap::getBaseObject(BlockId id)
{

	switch (id.objType)
	{
		case Solid::ID:  return m_solids[id.objIndex]; break;
		case CeilFloor::ID:  return m_cf[id.objIndex]; break;
		case Port::ID:  return m_ports[id.objIndex]; break;
		case Empty::ID:  return m_emptys[id.objIndex]; break;
	}

	return Block();
}

void BlockMap::addToBitmap(int x, int y, int layer, BlockId id)
{
	if (layer < 0)
	{
		getBaseObject(getBlockId(x, y, layer + 1)).m_prev = id;
	}
	else
	{
		if (layer == 0)
		{
			m_bitmap[y * 64 + x] = id;
			return;
		}
		getBaseObject(getBlockId(x, y, layer - 1)).m_next = id;
	}

}