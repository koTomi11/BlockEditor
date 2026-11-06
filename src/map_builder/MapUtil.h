#pragma once

#include <glm/glm.hpp>
#include <string>

struct MapUtil
{

	static std::string pointToString(glm::vec3 point)
	{
		std::string str;

		str.append("( "); str.append(std::to_string((int) point.x)); str.append(" ");
		str.append(std::to_string((int)point.y)); str.append(" ");
		str.append(std::to_string((int)point.z)); str.append(" )");


		return str;
	}

	static std::string textureAxistoString(glm::vec4 axis)
	{
		std::string str;

		str.append("[ "); str.append(std::to_string((int)axis.x)); str.append(" ");
		str.append(std::to_string((int)axis.y)); str.append(" ");
		str.append(std::to_string((int)axis.z)); str.append(" ");
		str.append(std::to_string((int)axis.w)); str.append(" ]");

		return str;
	}

	static std::string rotScaletoString(glm::vec3 rotScale)
	{
		std::string str;

		str.append(std::to_string((int)rotScale.x)); str.append(" ");
		str.append(std::to_string((int)rotScale.y)); str.append(" ");
		str.append(std::to_string((int)rotScale.z)); str.append(" ");
		

		return str;
	}

	static std::string stringPairToString(std::string str1, std::string str2)
	{
		std::string str;

		str.append("\""); str.append(str1); str.append("\" ");
		str.append("\""); str.append(str2); str.append("\"");

		return str;
	}

};
