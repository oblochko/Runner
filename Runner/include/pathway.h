#pragma once

#if !defined(_PUTHWAY_H_)
#define _PUTHWAY_H_

#include <ctime>
#include <random>

#include "square.h"
#include "bufferVertex.h"
#include "player.h"
#include "lightCube.h"

const int sizeTitle = 60;
const int sizePathway = 20; 
const int sizeLight = 8;
const GLfloat Long = 55;

class Pathway
{
public:
	Player player;
private:
	/*std::mt19937 gen(glfwGetTime());
	std::uniform_int_distribution<> uid(1, 9);
	std::uniform_int_distribution<> ulong(3, 7);*/
	std::mt19937 gen;
	std::uniform_int_distribution<> uid;
	std::uniform_int_distribution<> ulong;
	int currentLine;
private:
	Shader shaderProgram;
	Shader shaderProgramLamp;
	Shader shaderProgramLava;
	/*Shader shaderProgramTexture;
	Shader shaderProgram2Texture;*/
	vector<class Square*> vectorSquare;
	vector<class LightCube*> vectorLightCube;
	glm::vec3 directive;
	int mSizeTrain[sizePathway] = { 0 };
public:
	Pathway();
	void init();
	void generate();
	void generateMove(int key);
	void setSafety(int key, bool flag);
	void draw();
	void drawTile();
	void drawCube();
	void drawWalls();
	void drawLights();
	void drawVector(int key);
};

#endif
