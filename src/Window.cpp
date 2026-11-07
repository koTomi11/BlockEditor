#include "Window.h"
#include <iostream>

std::vector<IEventListener*> listeners;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	for (IEventListener* l : listeners)
	{
		l->keyPress(key);
	}
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
	for (IEventListener* l : listeners)
	{
		l->mouseMove((int)xpos, (int)ypos);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
}

void character_callback(GLFWwindow* window, unsigned int codepoint) {
	
}

Window::Window(int width, int height)
{

	m_width = width; m_height = height;

	if (!glfwInit()) {
		std::cerr << "Nem sikerült inicializálni a GLFW-t!" << std::endl;
		
	}

	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	m_window = glfwCreateWindow(m_width, m_height, "OpenGL + GLAD Teszt", NULL, NULL);
	if (!m_window) {
		std::cerr << "Nem sikerült létrehozni a GLFW ablakot!" << std::endl;
		glfwTerminate();
		
	}


	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCharCallback(m_window, character_callback);

	glfwMakeContextCurrent(m_window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Nem sikerült inicializálni a GLAD-et!" << std::endl;
		glfwTerminate();
		
	}
}



void Window::addListener(IEventListener* listener)
{
	listeners.push_back(listener);
}

void Window::poolEvent()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool Window::isClose()
{
	return glfwWindowShouldClose(m_window);
}


void Window::drawBuffer(unsigned char* pixels)
{
	glRasterPos2f(-1, -1);
	glDrawPixels(m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}