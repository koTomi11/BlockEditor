#pragma once

#include "../map_builder/MapBuilder.h"
#include "../IRender2d.h"
#include "../gui/GuiPanel.h"
#include "../BlockMap.h"




class Editor : public GuiPanel
{

public:

	BlockMap* m_blockMap;

	int m_currentLayer;
	int m_currentBlock;

	int m_gridSize;

	Editor(int x, int y, int width, int height);

	void update(IRender2d* ctx);
	void save(std::string fileName);


};