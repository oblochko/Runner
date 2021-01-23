//
//  glShape.h
//  OpenGL Application
//
//  Created by Cellyceos on 29/01/2014.
//  Copyright (c) 2014 Kirill Bravichev. All rights reserved.
//

#ifndef __glShape_h__
#define __glShape_h__

//Заголовочый файл Windows
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

//Заголовочный файл OpenGL
#if !defined(__gl_h_) && defined(_WIN32)
#include <gl/GL.h>
#elif !defined(__gl3_h_) && defined(__APPLE__)
#include <OpenGL/gl3.h>
#endif

//Заголовочный файл векторной математики
#ifndef __vmath_Header_File__
#include "vmath.h"
#endif

//#include <GL/glew.h>

#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLFW
#include <GLFW/glfw3.h>

#define MAX_VERTICES 1048576
#define MAX_INDICES  (MAX_VERTICES * 4)

class glShape {
	Vector3f* normals;
	Vector3f* tangents;
	Vector3f* vertices;
	Vector2f* texCoords;

	GLuint* indices;

	GLuint indexCount;
	GLuint vertexCount;

public:
	glShape(GLuint numVertices, GLuint numIndices);

	inline GLuint GetVertexCount() const { return vertexCount; }
	inline GLuint GetIndexCount() const { return indexCount; }

	inline const Vector3f* GetNormals() const { return normals; }
	inline const Vector3f* GetVertices() const { return vertices; }
	inline const Vector3f* GetTangents() const { return tangents; }
	inline const Vector2f* GetTexCoords() const { return texCoords; }

	inline GLuint* GetIndices() const { return indices; }

	static glShape* CreateCube(const GLfloat height = 1.0f, GLuint numberSlices = 10u);
	static glShape* CreatePlane(const GLfloat height = 1.0f, GLuint numberSlices = 10u);
	static glShape* CreateSphere(const GLuint numberSlices, const GLfloat radius = 0.3f);
	static glShape* CreateCylinder(const GLuint numberSlices, const GLfloat radius = 1.0f, const GLfloat height = 2.0f);
	static glShape* CreateCone(const GLuint numberSlices, const GLfloat topRadius = 0.0f, const GLfloat buttomRadius = 1.0f, const GLfloat height = 2.0f);
	static glShape* CreateTorus(const GLuint numberSlices, const GLuint numberRings, const GLfloat innerRadius = 0.25f, const GLfloat outterRadius = 1.0f);

	~glShape();
private:
	void CalculateTangent();
};
#endif /* defined(__glShape_h__) */