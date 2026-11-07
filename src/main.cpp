#include <glad/glad.h>   
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Render.h"


#include "map_builder/MapBuilder.h"
#include "editor/Editor.h"

#include "Window.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	
	Window w(800, 600);

	
	std::cout << "OpenGL Verzio: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Videokartya: " << glGetString(GL_RENDERER) << std::endl;

	
	glViewport(0, 0, 800, 600);

	Render render;
	render.initalize(800, 600);

	MapBuilder mb;

	
	for (int i = 0; i < 3; i++)
	{
		Brush b;
		b.initCube(500);
		b.move(i * 600, 0, 0);
		mb.brushs.push_back(b);
	}
	
	mb.save("bazdmeg.map");

	std::cout << MapUtil::stringPairToString("fasz", "szopo") <<std::endl;

	int te = render.loadImage("texture.jpg");

	Editor editor;

	for(int i=0;i<30;i++)
	editor.addBlock(i, 5, Block());
	editor.save("gecibe.map");

	
	render.loadFont("JetBrainsMono-Medium.ttf");
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	

	while (!w.isClose()) {
		
		w.poolEvent();

		
		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render.drawImage(te, 50, 50, 70, 80);

		render.setColor(0, 0, 0);
		render.drawString( 0, 200, "qwertzuiasd1234");
		
		render.setColor(230, 23, 230);
		
		
		render.fillCircle(400, 400, 100);
		render.setColor(100, 0, 12);
		render.fillRect(50, 50, 50, 50);

		//render.drawImage(render.m_fontAtlas, 0, 0, 400, 400);

		render.endFrame();

		
		w.swapBuffers();

	}

	
	glfwTerminate();
	return 0;
}