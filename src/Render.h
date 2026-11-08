#pragma once

#include <glad/glad.h>
#include <vector>
#include "Shader.h"
#include "IRender2d.h"

#include "Font.h"

struct Vertex
{
	float m_x, m_y;
	float m_u, m_v;
	unsigned char m_r, m_g, m_b, m_a;

	Vertex(float x, float y)
	{
		m_x = x; m_y = y; m_u = x / 500.0f; m_v = y / 700.0f; m_r = 255; m_g = 255; m_b = 255; m_a = 255;
	}

	Vertex(float x, float y, float u, float v)
	{
		m_x = x; m_y = y; m_u = u; m_v = v; m_r = 255; m_g = 255; m_b = 255; m_a = 255;
	}

	Vertex(float x, float y, float u, float v, unsigned char r, unsigned char g, unsigned char b)
	{
		m_x = x; m_y = y; m_u = u; m_v = v; m_r = r; m_g = g; m_b = b; m_a = 255;
	}

	Vertex(float x, float y, unsigned char r, unsigned char g, unsigned char b)
	{
		m_x = x; m_y = y; m_u = x / 500.0f; m_v = y / 700.0f; m_r = r; m_g = g; m_b = b; m_a = 255;
	}

};


struct DrawCmd
{
	GLuint texture;
	GLuint drawMode;
	GLuint first;
	GLuint count;
};


class Render : public IRender2d
{

public:
	Shader* shader;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_whiteTexture;
	GLuint m_fontAtlas;
	std::vector<Font> m_fonts;
	std::vector<DrawCmd> cmds;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	int m_posX, m_posY;
	

	unsigned char m_r, m_g, m_b;
	unsigned int lineWidth;

	void initalize(int width, int height);

	
	void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2);
	void drawLine(int x0, int y0, int x1, int y2);
	void drawRect(int x, int y, int width, int height);
	void drawString(int x, int y, std::string str);

	unsigned int loadImage(std::string fileName);
	unsigned int loadFont(std::string fileName);

	unsigned int loadImage(unsigned char* pixels, int width, int height, int nComps);

	 void drawImage(int id, int x, int y, int width, int height);

	 void fillRect(int x, int y, int width, int height);
	 void fillCircle(int x, int y, int r);

	 void setColor(unsigned char r, unsigned char g, unsigned char b);
	 void setLineWidth(int s);
	 void setPos(int x, int y);

	 void endFrame();


private:

	void allocateBuffer(GLuint buffer, GLuint target, GLuint usage, void* data, unsigned int size);
	GLuint loadTexture(std::string fileName);
};