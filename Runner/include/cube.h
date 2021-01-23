#pragma once

#if !defined(_CUBE_H_)
#define _CUBE_H_

#include "draw.h"

class Cube// : public Draw
{
public:
	glm::vec3 position;
	glm::vec3 color;
public:
	Cube();
	void draw();
	void move();
	void setColor();
};

#endif

