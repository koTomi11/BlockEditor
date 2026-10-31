#include "Shader.h"

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Shader::Shader(std::string vs, std::string fs)
{
	m_program = glCreateProgram();

	m_vs = loadShader(vs, GL_VERTEX_SHADER);
	m_fs = loadShader(fs, GL_FRAGMENT_SHADER);

	glAttachShader(m_program, m_vs);
	glAttachShader(m_program, m_fs);


	glLinkProgram(m_program);


}


GLuint Shader::loadShader(std::string src, GLuint type)
{
	std::string src2("F:\\Users\\asdf\\Desktop\\shaders\\");
	src2.append(src);
	std::string src3;

	std::ifstream file(src2);
	std::string line;
	
	while (std::getline(file, line)) {
		src3.append(line);
		src3.append("\n");
	}

	const GLchar*  string[1];

	string[0] = src3.c_str();
	size_t s = strlen(src3.c_str());

	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, string, NULL);
	glCompileShader(shaderId);


	return shaderId;
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
{
	
	glm::mat4 projMat = glm::ortho(left, right, bottom, top, zNear, zFar);
	GLuint location = glGetUniformLocation(m_program, "projMatrix");

	bind();
	glUniformMatrix4fv(location, 1, GL_FALSE, &projMat[0][0]);

}