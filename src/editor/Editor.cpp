#include "Editor.h"

#include <memory>

Editor::Editor()
{

	m_bitmap = new BlockId[64 * 64];
	memset(m_bitmap, 0, 64 * 64 * sizeof(BlockId));

	
}

void Editor::addBlock(int x, int y, Block block)
{
	int index = y * 64 + x;
	m_bitmap[index].objType = 1;
	m_bitmap[index].objIndex = m_blocks.size();
	m_blocks.push_back(block);

}

void Editor::save(std::string fileName)
{

	MapBuilder map;

	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			if (m_bitmap[y * 64 + x].objType != 0)
			{
				Block b = m_blocks[m_bitmap[y * 64 + x].objIndex];

				map.addBlock(x * 100, y * 100);

			}
			
		}
	}

	map.save("bazdmeg.map");

}