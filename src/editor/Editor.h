#pragma once

#include "../map_builder/MapBuilder.h"
#include "../IRender2d.h"
#include "../gui/GuiPanel.h"
#include "../BlockMap.h"

#include "../gui/GuiGrid.h"

class Editor : public GuiPanel, public IGridInterface
{

public:

	BlockMap* m_blockMap;

	int m_currentLayer;
	int m_currentBlock;

	int m_gridSize;

	GuiGrid* m_grid;

	Editor(int x, int y, int width, int height);

	void update(IRender2d* ctx);
	void save(std::string fileName);

	void onClick(int x, int y) override;
	void draw(IRender2d* ctx, int x, int y, int width, int height) override;

};