#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{

public:

	GLuint m_program;
	GLuint m_vs;
	GLuint m_fs;

	Shader(std::string vs, std::string fs)
	{
		m_program = glCreateProgram();
	}


};