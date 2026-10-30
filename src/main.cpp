#include <glad/glad.h>   // ⚠️ Ennek KÖTELEZŐEN az elsőnek kell lennie!
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Render.h"

#include "MapBuilder.h"

// Függvény a billentyűzet figyelésére (ESC gombra bezárja az ablakot)
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// 1. GLFW inicializálása
	if (!glfwInit()) {
		std::cerr << "Nem sikerült inicializálni a GLFW-t!" << std::endl;
		return -1;
	}

	// OpenGL verzió beállítása (Modern Core Profile, pl. 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. Ablak létrehozása
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL + GLAD Teszt", NULL, NULL);
	if (!window) {
		std::cerr << "Nem sikerült létrehozni a GLFW ablakot!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 3. GLAD INICIALIZÁLÁSA (Ez tölti be az OpenGL függvényeket)
	// A glfwGetProcAddress segítségével a GLAD automatikusan megkeresi a videokártyád illesztőprogramját
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Nem sikerült inicializálni a GLAD-et!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Sikeres betöltés esetén kiírjuk a videokártyád és az OpenGL verzióját
	std::cout << "OpenGL Verzio: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Videokartya: " << glGetString(GL_RENDERER) << std::endl;

	// A rajzolási felület méretének beállítása
	glViewport(0, 0, 800, 600);

	Render render;
	render.initalize();

	MapBuilder mb;
	mb.save("bazdmeg.map");

	std::cout << MapUtil::stringPairToString("fasz", "szopo") <<std::endl;

	// 4. Fő renderelési ciklus
	while (!glfwWindowShouldClose(window)) {
		// Gombnyomások kezelése
		processInput(window);

		// Háttér letisztítása egy szép sötétkék (teal) színre
		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (int i = 0; i < 2; i++)
		{
			render.drawLine(i / 50.0f, 0, i / 20.0f, 0.5);
		}

	

		render.render();

		// Pufferek cseréje és események lekérdezése
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 5. Erőforrások felszabadítása
	glfwTerminate();
	return 0;
}