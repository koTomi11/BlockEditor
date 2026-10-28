#pragma once

#include <glad/glad.h>
#include <vector>

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

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	std::vector<DrawCmd> cmds;
	std::vector<float> vertices;

	void initalize();

	void render();
	void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2);
	void drawLine(float x0, float y0, float x1, float y2);

private:

	void allocateBuffer(GLuint buffer, GLuint target, GLuint usage, void* data, unsigned int size);

};