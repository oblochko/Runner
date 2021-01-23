#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "../include/scene.h"

// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	Scene scene;
	
	scene.init();
	// Game loop
	while (!glfwWindowShouldClose(scene.window))
	{
		scene.event();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.render();

		glfwSwapBuffers(scene.window);
	}

	glfwTerminate();
	return 0;
}

