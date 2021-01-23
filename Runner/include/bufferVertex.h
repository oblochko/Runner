#pragma once

#if !defined(_BUFFERVERTEX_H_)
#define _BUFFERVERTEX_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glShape.h"

using namespace std;

enum class Figure
{
	Square = 0,
	Cube,
	Sphere,
	Lava,
	Stones
};

class BufferVertex
{
public:
	static BufferVertex bufferVertex;
private:
	vector< vector<GLfloat> > vectorVertex;
	vector< GLuint > vectorVAO;
	vector< GLuint > vectorVBO;
	vector< GLuint > verctorTexture;
public:
	glShape* sphere;
public:
	void generate();
	void init(vector<GLfloat> vertices);
	void initEBO(vector<GLfloat> vertices);
	void initTexture(string path);
	GLuint getVAO(int ID);
	GLuint getTexture(Figure ID);
};
#endif

