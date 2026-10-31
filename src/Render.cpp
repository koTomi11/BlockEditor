#include "Render.h"
#include <math.h>

#include <iostream>
#include <stb_image.h>

#include <fstream>

void Render::initalize()
{

	shader = new Shader("Shader.vs", "Shader.fs");
	shader->setProjectionMatrix(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	std::ofstream file("geci.txt");

	file.close();

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

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 28, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 28, (void*)8);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 28, (void*)16);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void Render::render()
{
	shader->bind();
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	if (vertices.size() > 0)
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);

	for (DrawCmd cmd : cmds)
	{
		glDrawArrays(cmd.drawMode, cmd.first, cmd.count);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	vertices.clear();
	cmds.clear();
}

void Render::drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2)
{

	DrawCmd cmd;
	cmd.count = 3;
	cmd.first = vertices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmds.push_back(cmd);

	vertices.push_back(Vertex(x0,y0));
	vertices.push_back(Vertex(x1, y1));
	vertices.push_back(Vertex(x2, y2));

}

void Render::drawLine(float x0, float y0, float x1, float y1)
{

	float v = 3;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float length = sqrtf(dx * dx + dy * dy);

	float nx = -dy / length;
	float ny = dy / length;

	float offsetX = nx * (v * 0.5f);
	float offsetY = ny * (v * 0.5f);

	DrawCmd cmd;
	cmd.count = 6;
	cmd.first = vertices.size();
	cmd.drawMode = GL_TRIANGLES;
	cmds.push_back(cmd);

	vertices.push_back(Vertex(x0 + offsetX, y0 + offsetY));
	vertices.push_back(Vertex(x0 - offsetX, y0 - offsetY));
	vertices.push_back(Vertex(x1 + offsetX, y1 + offsetY));

	vertices.push_back(Vertex(x1 - offsetX, y1 - offsetY));
	vertices.push_back(Vertex(x0 - offsetX, y0 - offsetY));
	vertices.push_back(Vertex(x1 + offsetX, y1 + offsetY));
	
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

	// Az OpenGL az Y tengelyt alulról felfelé számolja, 
	// a képek többsége viszont felülrõl lefelé tárolja a pixeleket.
	// Ezzel a sorral megfordítjuk a képet függõlegesen a betöltéskor:
	//stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		// Dinamikusan meghatározzuk a kép formátumát (JPG = RGB, PNG = RGBA)
		GLenum format;
		if (nrComponents == 1)      format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);

		// 1. Képadatok feltöltése a GPU-ra
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		// 2. Mipmapek (kisebb felbontású verziók) automatikus generálása a távoli nézethez
		glGenerateMipmap(GL_TEXTURE_2D);

		// 3. Textúra paraméterek beállítása (Wrapping és Filtering)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 4. A CPU memóriába betöltött nyers képadatokat felszabadítjuk, mert már a GPU-n vannak
		stbi_image_free(data);
		std::cout << "Texture sikeresen betoltve: " << path << std::endl;
	}
	else {
		std::cout << "Hiba: Nem sikerult a texturat betolteni a kovetkezo utvonalrol: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}