#pragma once

#if !defined(_PLAYER_H_)
#define _PLAYER_H_

#include "square.h"
#include "bufferVertex.h"

class Player
{
private:
	Shader shaderProgramTextrue;
	GLfloat radius;
public:
	glm::vec3 position;
	glm::vec3 color;
	int sizeTitle;
	int sizeLine;
public:
	bool right;
	bool left;
	bool life;
	int currentColumn;
public:
	Player();
	void init();
	void draw();
	void draw(Shader& shader);
	glm::mat4 move();
	void collision(vector<class Square*> vector, int _current);
	int getIndex(GLfloat x, GLfloat z);
	void setColor();
};

#endif

