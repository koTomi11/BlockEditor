#pragma once

#include <glad/glad.h>
#include <vector>
#include "Shader.h"

struct Vertex
{
	float m_x, m_y;
	float m_u, m_v;
	float m_r, m_g, m_b;

	Vertex(float x, float y)
	{
		m_x = x; m_y = y; m_u = x / 500.0f; m_v = y / 700.0f; m_r = 0.0; m_g = 0.2; m_b = 1;
	}

};


struct DrawCmd
{
	GLuint texture;
	GLuint drawMode;
	GLuint first;
	GLuint count;
};


class Render
{

public:
	Shader* shader;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	std::vector<DrawCmd> cmds;
	std::vector<Vertex> vertices;

	void initalize();

	void render();
	void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2);
	void drawLine(float x0, float y0, float x1, float y2);

private:

	void allocateBuffer(GLuint buffer, GLuint target, GLuint usage, void* data, unsigned int size);
	GLuint loadTexture(std::string fileName);
};