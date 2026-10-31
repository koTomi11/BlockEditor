#include <glad/glad.h>   
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Render.h"

#include "MapBuilder.h"


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	
	if (!glfwInit()) {
		std::cerr << "Nem sikerült inicializálni a GLFW-t!" << std::endl;
		return -1;
	}

	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL + GLAD Teszt", NULL, NULL);
	if (!window) {
		std::cerr << "Nem sikerült létrehozni a GLFW ablakot!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Nem sikerült inicializálni a GLAD-et!" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	std::cout << "OpenGL Verzio: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Videokartya: " << glGetString(GL_RENDERER) << std::endl;

	
	glViewport(0, 0, 800, 600);

	Render render;
	render.initalize(800, 600);

	MapBuilder mb;
	mb.save("bazdmeg.map");

	std::cout << MapUtil::stringPairToString("fasz", "szopo") <<std::endl;

	int te = render.loadImage("texture.jpg");
	
	while (!glfwWindowShouldClose(window)) {
		
		processInput(window);

		
		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	

		//render.drawImage(te, 50, 50, 70, 80);

		render.setColor(20, 100, 10);
		render.fillRect(50, 50, 50, 50);

		render.setColor(20, 50, 100);
		render.fillRect(300, 50, 50, 50);

		render.drawImage(te, 200, 200, 80, 40);

		render.drawLine(380, 380, 350, 350);

		render.endFrame();

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}