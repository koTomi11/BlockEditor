#include "MapBuilder.h"

#include <fstream>
#include <iostream>

Plane::Plane(int px0, int py0, int pz0,
	int px1, int py1, int pz1,
	int px2, int py2, int pz2,
	std::string texture)
{
	m_point1 = glm::vec3(px0, py0, pz0);
	m_point2 = glm::vec3(px1, py1, pz1);
	m_point2 = glm::vec3(px1, py1, pz1);
	m_texture = texture;
}

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
		file << MapUtil::stringPairToString("wad", "") << "\n";



		file << "}";
		
		file.close();
	}
}