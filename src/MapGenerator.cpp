#include "MapGenerator.h"


MapBuilder MapGenerator::generate(BlockMap* blocks)
{
	MapBuilder map;

	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{

			BlockId id = blocks->getBlockId(x, y, 0);
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

				Port p = blocks->m_ports[id.objIndex];

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

	return map;
}