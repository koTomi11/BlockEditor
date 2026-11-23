#pragma once

#include "BlockMap.h"
#include "map_builder/MapBuilder.h"

#define SIZE 128

class MapGenerator
{

public:

	MapBuilder m_map;

	MapBuilder generate(BlockMap* blocks);

};