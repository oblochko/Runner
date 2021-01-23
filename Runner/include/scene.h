#pragma once

#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h"
#include "../include/camera.h"
#include "../include/pathway.h"


class Scene
{
public:
	GLFWwindow* window = NULL;
	int k;
	bool keys[1024];
private:
	Pathway pathway;
private:	
	GLfloat lastX = WIDTH / 2.0;
	GLfloat lastY = HEIGHT / 2.0;
	
	// Light attributes
	glm::vec3 lightPos;

	// Deltatime
	GLfloat lastFrame = 0.0f;

	vector<glm::vec3> cubePositions;
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:
	Scene();
	void main(GLFWwindow* window = NULL);
	void init();
	void event();
	void render();
	void onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	void onMouse(GLFWwindow* window, double xpos, double ypos);
	void onScroll(GLFWwindow* window, double xoffset, double yoffset);
	void do_movement();
};

#endif
