#include "MapGenerator.h"


MapBuilder MapGenerator::generate(BlockMap* blocks)
{

	for (Entity e : blocks->m_entityes)
	{
		m_map.addEntity(e.m_x * SIZE, e.m_y * SIZE, e.m_layer * SIZE * 3, e.m_type);
	}

	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			for (int l = -2; l < 4; l++)
			{

				BlockId id = blocks->getBlockId(x, y, l);
				if (id.objType == 0) continue;

				int blockX = x * SIZE;
				int blockY = y * SIZE;

				switch (id.objType)
				{

				case Solid::ID:
					m_map.addBlock(blockX, blockY, 0 + l * SIZE * 3);
					break;


				case CeilFloor::ID:
					m_map.addBlock(blockX, blockY, SIZE + l * SIZE * 3);
					m_map.addBlock(blockX, blockY, -SIZE + l * SIZE * 3);
					break;

				case Port::ID:

					Port p = blocks->m_ports[id.objIndex];

					if (p.m_up)
					{
						m_map.addBlock(blockX + SIZE, blockY, SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX - SIZE, blockY, SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY + SIZE, SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY - SIZE, SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY, -SIZE + l * SIZE * 3);
					}
					else
					{
						m_map.addBlock(blockX + SIZE, blockY, -SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX - SIZE, blockY, -SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY + SIZE, -SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY - SIZE, -SIZE * 2 + l * SIZE * 3);
						m_map.addBlock(blockX, blockY, SIZE + l * SIZE * 3);
					}

					break;

				}
			}
		}

	}
		return m_map;
	}