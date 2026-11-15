#include "MapGenerator.h"


MapBuilder MapGenerator::generate(BlockMap* blocks)
{
	MapBuilder map;
for(int l=0;l<2;l++)
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{

			BlockId id = blocks->getBlockId(x, y, l);
			if (id.objType == 0) continue;

			int blockX = x * 100;
			int blockY = y * 100;

			switch (id.objType)
			{

			case Solid::ID:
				map.addBlock(blockX, blockY, 0 + l * 300);
				break;


			case CeilFloor::ID:
				map.addBlock(blockX, blockY, 100 + l * 300);
				map.addBlock(blockX, blockY, -100 + l * 300);
				break;

			case Port::ID:

				Port p = blocks->m_ports[id.objIndex];

				if (p.m_up)
				{
					map.addBlock(blockX + 100, blockY, 200 + l * 300);
					map.addBlock(blockX - 100, blockY, 200 + l * 300);
					map.addBlock(blockX, blockY + 100, 200 + l * 300);
					map.addBlock(blockX, blockY - 100, 200 + l * 300);
					map.addBlock(blockX, blockY, -100 + l * 300);
				}
				else
				{
					map.addBlock(blockX + 100, blockY, -200 + l * 300);
					map.addBlock(blockX - 100, blockY, -200 + l * 300);
					map.addBlock(blockX, blockY + 100, -200 + l * 300);
					map.addBlock(blockX, blockY - 100, -200 + l * 300);
					map.addBlock(blockX, blockY, 100 + l * 300);
				}

				break;

			}
		}
	}

	return map;
}