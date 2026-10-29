#include "Render.h"
#include <math.h>

#include <iostream>

void Render::initalize()
{

	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);



	allocateBuffer(m_vbo, GL_ARRAY_BUFFER, GL_STREAM_DRAW, nullptr, 1024);
	allocateBuffer(m_ibo, GL_ELEMENT_ARRAY_BUFFER, GL_STREAM_DRAW, nullptr, 512);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, (void*)0);

	glDisableVertexAttribArray(0);

}

void Render::render()
{

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() , &vertices[0]);
	for (DrawCmd cmd : cmds)
	{
		glDrawArrays(cmd.drawMode, cmd.first, cmd.count);
	}
	glDisableVertexAttribArray(0);

	vertices.clear();
	cmds.clear();
}

void Render::drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2)
{

	DrawCmd cmd;
	cmd.count = 2;
	cmd.first = vertices.size() / 2;
	cmd.drawMode = GL_TRIANGLES;
	cmds.push_back(cmd);


	vertices.push_back(x0);  vertices.push_back(y0);
	vertices.push_back(x1);  vertices.push_back(y1);
	vertices.push_back(x2);  vertices.push_back(y2);
}

void Render::drawLine(float x0, float y0, float x1, float y1)
{

	float v = 0.003;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float length = sqrtf(dx * dx + dy * dy);

	float nx = -dy / length;
	float ny = dy / length;

	float offsetX = nx * (v * 0.5f);
	float offsetY = ny * (v * 0.5f);

	DrawCmd cmd;
	cmd.count = 6;
	cmd.first = vertices.size() / 2;
	cmd.drawMode = GL_TRIANGLES;
	cmds.push_back(cmd);

	

	vertices.push_back(x0 + offsetX); vertices.push_back(y0 + offsetY);
	vertices.push_back(x0 - offsetX); vertices.push_back(y0 - offsetY);
	vertices.push_back(x1 + offsetX); vertices.push_back(y1 + offsetY);


	vertices.push_back(x1 - offsetX); vertices.push_back(y1 - offsetY);
	vertices.push_back(x0 - offsetX); vertices.push_back(y0 - offsetY);
	vertices.push_back(x1 + offsetX); vertices.push_back(y1 + offsetY);
	
}

void Render::allocateBuffer(GLuint buffer, GLuint target, GLuint usage, void* data, unsigned int size)
{

	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);

}