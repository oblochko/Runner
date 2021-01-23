#include "../include/draw.h"

void Draw::initShader(string vertexPuth, string fragmentPuth)
{
	shaderProgram.init(vertexPuth.c_str(), fragmentPuth.c_str());
}
