#pragma once

#if !defined(_SQUARE_H_)
#define _SQUARE_H_

#include "draw.h"

enum class Type {
	None = 0,
	Train,
	Safety
};

class Square// : public Draw
{
public:
	Type type;
	Type futureType;
	int id;	
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 colorCube;
public:
	Square();
	void draw();
	void move();
	void setColor();
};

#endif
