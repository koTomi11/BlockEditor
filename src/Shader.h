#pragma once

#include <glad/glad.h>
#include <string>
#include "Shader.h"

class Shader
{

public:

	
	GLuint m_program;
	GLuint m_vs;
	GLuint m_fs;

	Shader(std::string vs, std::string fs);
	GLuint loadShader(std::string src, GLuint type);
	void bind();
	void unbind();

};