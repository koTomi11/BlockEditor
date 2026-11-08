#include "Window.h"
#include <iostream>
#include "Input.h"


std::vector<IEventListener*> listeners;
Input input;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{

	switch (action)
	{
	case GLFW_PRESS:   input.mouseButton[key] = true; break;
	case GLFW_RELEASE:  input.mouseButton[key] = false; break;
	}

}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
	

	input.m_mouseX = (int)xpos;
	input.m_mouseY = (int)ypos;

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:   input.mouseButton[button] = true; break;
	case GLFW_RELEASE:  input.mouseButton[button] = false; break;
	}
}

void character_callback(GLFWwindow* window, unsigned int codepoint) 
{
	input.m_typedText.push_back((char)codepoint);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << xoffset << "  " << yoffset << std::endl;
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
	std::cout << "Behuzott elemek szama: " << count << std::endl;

	for (int i = 0; i < count; i++)
	{
		// A paths[i] tartalmazza a teljes eleresi utat (pl. "C:\\Users\\Nev\\kep.png")
		std::cout << "  [" << i << "]: " << paths[i] << std::endl;
	}
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
	glfwSetScrollCallback(m_window, scroll_callback);
	glfwSetDropCallback(m_window, drop_callback);

	glfwMakeContextCurrent(m_window);

	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Nem sikerült inicializálni a GLAD-et!" << std::endl;
		glfwTerminate();
		
	}

	std::cout << "OpenGL Verzio: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Videokartya: " << glGetString(GL_RENDERER) << std::endl;

	glViewport(0, 0, 800, 600);

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