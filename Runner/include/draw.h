#pragma once

#if !defined(_DRAW_H_)
#define _DRAW_H_

#include <iostream>
#include "shader.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <array>

// 3D figure
//#include "glShape.h"
#include "camera.h"
#include "shader.h"

#include <math.h>
//const GLuint WIDTH = 800, HEIGHT = 800;
#define pi 3.14

enum Color {
	Red = 0,
	Orange,
	Yellow,
	Green,
	Ñyan,
	Blue,
	Purple
};

class Draw
{
protected:
	Shader shaderProgram;
public:
	Draw();
	//virtual void draw() = 0;
	void initShader(string vertexPuth, string fragmentPuth);
};

#endif