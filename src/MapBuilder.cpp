#include "MapBuilder.h"

#include <fstream>
#include <iostream>



std::string Plane::toString()
{
	std::string str;

	str.append(MapUtil::pointToString(m_point1)); str.append(" ");
	str.append(MapUtil::pointToString(m_point2)); str.append(" ");
	str.append(MapUtil::pointToString(m_point3)); str.append(" ");
	str.append(m_texture); str.append(" ");
	str.append(MapUtil::textureAxistoString(m_uAxis)); str.append(" ");
	str.append(MapUtil::textureAxistoString(m_vAxis)); str.append(" ");
	str.append(MapUtil::rotScaletoString(m_rotScale)); 
		
	return str;
}

std::string Brush::toString()
{
	std::string str;

	str.append("{\n");
	for (Plane p : planes)
	{
		str.append(p.toString()); str.append("\n");
	}
	str.append("}");

	return str;
}

void Brush::init()
{

}



void Brush::initCube(int size)
{
	
	float h = size / 2.0f;

	planes.push_back(Plane(-h,h,h,   h,h,h,   h,-h,h,   "NONE",    1,0,0,0, 0,-1,0,0, 0,1,1));
	planes.push_back(Plane(-h,-h,-h, h,-h,-h, h,h,-h, "NONE",      1,0,0,0, 0,-1,0,0, 0,1,1));
	planes.push_back(Plane(-h,h,h,   -h,-h,h,   -h,-h,-h,  "NONE", 0,1,0,0, 0,0,-1,0, 0,1,1));

	planes.push_back(Plane(h,h,-h,  h,-h,-h, h,-h,h, "NONE",        0,1,0,0, 0,0,-1,0, 0,1,1));
	planes.push_back(Plane(h,h,h,   -h,h,h,  -h,h,-h,  "NONE",      1,0,0,0, 0,0,-1,0, 0,1,1));
	planes.push_back(Plane(h,-h,-h,  -h,-h,-h,  -h,-h,h, "NONE",    1,0,0,0, 0,0,-1,0, 0,1,1));

}

void Brush::move(int x, int y, int z)
{
	for (Plane& p : planes)
	{
		p.move(x, y, z);

	}
}

void MapBuilder::addBlock(int x, int y)
{
	Brush b;
	b.initCube(100);
	b.move(x, y, 0);
	brushs.push_back(b);
}

void MapBuilder::save(std::string fileName)
{
	

	std::string path("F:\\Users\\asdf\\Desktop\\");
	path.append(fileName);

	std::ofstream file(path);

	if (file.is_open())
	{

		file << "{\n";
		file << MapUtil::stringPairToString("classname", "worldspawn") << "\n";
		file << MapUtil::stringPairToString("mapversion", "220") << "\n";
		file << MapUtil::stringPairToString("wad", "\\hammer\\tools\\zhlt\\zhlt.wad;\\hammer\\tools\\zhlt\\map.wad") << "\n";

		for (int i = 0; i < brushs.size(); i++)
		{
			file << brushs[i].toString() << "\n";
		}

		file << "}\n";
		
		file.close();
	}
}