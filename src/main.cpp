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

#include "gui/GuiGrid.h"

#include "gui/GuiMenuBar.h"
#include "gui/GuiTexturedButton.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	
	Window w(800, 600);
	Render render;
	render.initalize(w.getWidth(), w.getHeight());

	Editor editor(0, 0, w.getWidth(), w.getHeight());
	render.loadFont("JetBrainsMono-Medium.ttf");

	int t = render.loadImage("texture.jpg");
	editor.addChild(new GuiTexturedButton(100, 600, t, 0, &editor));

	
	while (!w.isClose()) {
		
		w.poolEvent();
		editor.update(&render);

		
		//mb.draw(&render);

		render.endFrame();
		w.swapBuffers();

	}

	//glfwTerminate();

	editor.save("out.map");

	return 0;
}