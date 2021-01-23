#include "../include/lightCube.h"

LightCube::LightCube() : position(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f)
{
}

void LightCube::generate(vector<class Square*> vector, int _current)
{
	GLfloat xangle = -0.5f - sqrt(2) / 4;
	GLfloat xsheer = -0.5f - sqrt(2) / 2;
	GLfloat yangle = sqrt(2) / 4;
	GLfloat rCube = 0.2f;
	if (_current % 15 == 0)
	{
		id = _current;
		//glm::vec3 pos(vector[_current]->position.x - 1.0f + xsheer + rCube / 2, yangle * 2 + 2.0f - rCube / 2, vector[_current]->position.z);
		position = { vector[_current]->position.x - 1.0f + xsheer + rCube / 2, yangle * 2 + 2.0f - rCube / 2, vector[_current]->position.z };
	}
	if (_current % 15 == 2)
	{
		id = _current;
		//glm::vec3 pos(vector[_current]->position.x + 1.0f - xsheer - rCube / 2, yangle * 2 + 2.0f - rCube / 2, vector[_current]->position.z);
		position = { vector[_current]->position.x + 1.0f - xsheer - rCube / 2, yangle * 2 + 2.0f - rCube / 2, vector[_current]->position.z };
	}
}
