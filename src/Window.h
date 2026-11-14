#pragma once

#include <glad/glad.h>   

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "IEventListener.h"
#include <vector>

class Window
{

public:

	GLFWwindow* m_window;
	int m_width, m_height;
	

	Window(int width, int height);

	void addListener(IEventListener* listener);

	void poolEvent();
	void swapBuffers();
	bool isClose();
	void drawBuffer(unsigned char* pixels);
	int getWidth();
	int getHeight();
};