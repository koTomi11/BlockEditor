#pragma once

#include <string>
#include <glm/glm.hpp>
#include "MapUtil.h"
#include <vector>


class Plane
{

public:

	std::string m_texture;
	glm::vec3 m_point1, m_point2, m_point3;
	glm::vec4 m_uAxis, m_vAxis;
	glm::vec3 m_rotScale;

	std::string toString();

	Plane(int px0, int py0, int pz0,
		int px1, int py1, int pz1,
		int px2, int py2, int pz2,
		std::string texture = "AAATRIGGER")
	{
		m_point1 = glm::vec3(px0, py0, pz0);
		m_point2 = glm::vec3(px1, py1, pz1);
		m_point3 = glm::vec3(px2, py2, pz2);
		m_texture = texture;
		m_uAxis = glm::vec4(0, 0, 0, 0);
		m_vAxis = glm::vec4(0, 0, 0, 0);
		m_rotScale = glm::vec3(0, 0, 1);
	}

	Plane(int px0, int py0, int pz0,
		int px1, int py1, int pz1,
		int px2, int py2, int pz2,
		std::string texture,
		float ux, float uy, float uz, float us,
		float vx, float vy, float vz, float vs,
		float rx, float ry, float s
	)
	{

		m_point1 = glm::vec3(px0, py0, pz0);
		m_point2 = glm::vec3(px1, py1, pz1);
		m_point3 = glm::vec3(px2, py2, pz2);
		m_texture = texture;
		m_uAxis = glm::vec4(ux, uy, uz, us);
		m_vAxis = glm::vec4(vx, vy, vz, vs);
		m_rotScale  = glm::vec3(rx, ry, s);

	}

	void move(int x, int y, int z)
	{
		m_point1.x += x; m_point1.y += y; m_point1.z += z;
		m_point2.x += x; m_point2.y += y; m_point2.z += z;
		m_point3.x += x; m_point3.y += y; m_point3.z += z;
	}

};

class Brush
{

public:

	

	std::vector<Plane> planes;

	void init();

	std::string toString();

	void initCube(int size);

	void move(int x, int y, int z);

};

class MapBuilder
{

public:

	std::vector<Brush> brushs;

	void save(std::string fileName);

};