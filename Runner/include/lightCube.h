#pragma once

#if !defined(_LIGHTCUBE_H_)
#define _LIGHTCUBE_H_

#include "square.h"
#include "bufferVertex.h"

class LightCube// : public Draw
{
public:
	glm::vec3 position;
	glm::vec3 color;
	int id;
public:
	LightCube();
	void generate(vector<class Square*> vector, int _current);
};

#endif
