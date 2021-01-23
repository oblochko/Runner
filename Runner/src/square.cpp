#include "../include/square.h"

Square::Square()
{
	//initShader("shaders/vertex_shader.txt", "shaders/fragment_shader.txt");
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	GLfloat x = (float(rand() % 100)) / 100;
	GLfloat y = (float(rand() % 100)) / 100;
	GLfloat z = (float(rand() % 100)) / 100;
	color = { x, y, z };
	x = (float(rand() % 100)) / 100;
	y = (float(rand() % 100)) / 100;
	z = (float(rand() % 100)) / 100;
	colorCube = { x, y, z };
	type = Type::None;
	futureType = Type::None;
}

void Square::draw()
{

}

void Square::setColor()
{
	color = { 0.0f, 1.0f, 0.0f };	
}
