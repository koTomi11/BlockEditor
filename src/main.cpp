#include <glad/glad.h>   
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Render.h"


#include "map_builder/MapBuilder.h"
#include "editor/Editor.h"

#include "Window.h"

#include "gui/GraphicsInterface.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	
	Window w(800, 600);

	
	

	Render render;
	render.initalize(800, 600);

	Editor editor;
	render.loadFont("JetBrainsMono-Medium.ttf");
	
	while (!w.isClose()) {
		
		w.poolEvent();
		editor.update(&render, 0, 0, false);

		render.endFrame();
		w.swapBuffers();

	}

	glfwTerminate();

	editor.save("out.map");

	return 0;
}