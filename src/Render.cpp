#include "Render.h"
#include <math.h>

#include <iostream>
#include <stb_image.h>

#include <fstream>

void Render::initalize(int width, int height)
{

	shader = new Shader("Shader.vs", "Shader.fs");
	shader->setProjectionMatrix(0.0f, width, height, 0.0f, -1.0f, 1.0f);


	GLuint text = loadTexture("fasza.jpg");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, text);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);




	allocateBuffer(m_vbo, GL_ARRAY_BUFFER, GL_STREAM_DRAW, nullptr, 1024 * 20);
	allocateBuffer(m_ibo, GL_ELEMENT_ARRAY_BUFFER, GL_STREAM_DRAW, nullptr, 512);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 20, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 20, (void*)8);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 20, (void*)16);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Render::endFrame()
{
	shader->bind();
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	if (m_vertices.size() > 0)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex), &m_vertices[0]);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(unsigned int), &m_indices[0]);
	}
	

	for (DrawCmd cmd : cmds)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cmd.texture);

		glDrawElements(GL_TRIANGLES, cmd.count, GL_UNSIGNED_INT,(void*) (cmd.first * 4));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	m_vertices.clear();
	m_indices.clear();
	cmds.clear();
}

void Render::drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2)
{

	DrawCmd cmd;
	cmd.count = 3;
	cmd.first = m_indices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmds.push_back(cmd);

	unsigned int base = m_vertices.size();

	m_vertices.push_back(Vertex(x0,y0));
	m_vertices.push_back(Vertex(x1, y1));
	m_vertices.push_back(Vertex(x2, y2));

	m_indices.push_back(base + 0); 	m_indices.push_back(base + 1); 	m_indices.push_back(base + 2);

}

void Render::drawLine(int x0, int y0, int x1, int y1)
{

	float v = 2;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float length = sqrtf(dx * dx + dy * dy);

	float nx = -dy / length;
	float ny = dy / length;

	float offsetX = nx * (v * 0.5f);
	float offsetY = ny * (v * 0.5f);

	DrawCmd cmd;
	cmd.count = 6;
	cmd.first = m_indices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmd.texture = 0;
	cmds.push_back(cmd);

	unsigned int base = m_vertices.size();

	m_vertices.push_back(Vertex(x0 + offsetX, y0 + offsetY, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x0 - offsetX, y0 - offsetY, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x1 + offsetX, y1 + offsetY, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x1 - offsetX, y1 - offsetY, m_r, m_g, m_b));
	
	m_indices.push_back(base + 0); m_indices.push_back(base + 1); m_indices.push_back(base + 2);
	m_indices.push_back(base + 3); m_indices.push_back(base + 1); m_indices.push_back(base + 2);
	
}

int Render::loadImage(std::string fileName)
{
	return (int) loadTexture(fileName);
}

void Render::drawImage(int id, int x, int y, int width, int height)
{
	DrawCmd cmd;
	cmd.count = 6;
	cmd.first = m_indices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmd.texture = id;
	cmds.push_back(cmd);

	unsigned int base = m_vertices.size();

	m_vertices.push_back(Vertex(x + width, y + height,1,1));
	m_vertices.push_back(Vertex(x + width, y,1,0));
	m_vertices.push_back(Vertex(x, y,0,0));
	m_vertices.push_back(Vertex(x, y + height,0,1));

	m_indices.push_back(base + 0); m_indices.push_back(base + 1); m_indices.push_back(base + 3);
	m_indices.push_back(base + 1); m_indices.push_back(base + 2); m_indices.push_back(base + 3);

}

void Render::fillRect(int x, int y, int width, int height)
{
	DrawCmd cmd;
	cmd.count = 6;
	cmd.first = m_indices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmd.texture = 0;
	cmds.push_back(cmd);

	unsigned int base = m_vertices.size();

	m_vertices.push_back(Vertex(x + width,y + height, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x + width, y, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x, y, m_r, m_g, m_b));
	m_vertices.push_back(Vertex(x, y + height, m_r, m_g, m_b));

	m_indices.push_back(base + 0); m_indices.push_back(base + 1); m_indices.push_back(base + 3);
	m_indices.push_back(base + 1); m_indices.push_back(base + 2); m_indices.push_back(base + 3);


}

void Render::fillOval(int x, int y, int width, int height)
{

}

void Render::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_r = r; m_g = g; m_b = b;
}

void Render::allocateBuffer(GLuint buffer, GLuint target, GLuint usage, void* data, unsigned int size)
{

	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);

}

GLuint Render::loadTexture(std::string fileName)
{

	std::string path("F:\\Users\\asdf\\Desktop\\textures\\");
	path.append(fileName);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;

	

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		
		GLenum format;
		if (nrComponents == 1)      format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);

		
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		
		glGenerateMipmap(GL_TEXTURE_2D);

		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		
		stbi_image_free(data);
		std::cout << "Texture sikeresen betoltve: " << path << std::endl;
	}
	else {
		std::cout << "Hiba: Nem sikerult a texturat betolteni a kovetkezo utvonalrol: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}