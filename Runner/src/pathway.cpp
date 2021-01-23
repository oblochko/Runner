#include "../include/pathway.h"

Pathway::Pathway() : gen(time(NULL)), uid(1, 5), ulong(3, 5), currentLine(0)
{
	glm::vec3 front(0.0f, 0.0f, 1.0f);
	glm::vec3 position(0.0f, 0.0f, 0.0f);
	directive = glm::normalize(front - position);
}

void Pathway::init()
{
	shaderProgram.init("shaders/vertex_shader.txt", "shaders/lighting_fragment.txt");
	shaderProgramLamp.init("shaders/vertex_shader.txt", "shaders/lamp_fragment.txt");
	shaderProgramLava.init("shaders/vertex_shader.txt", "shaders/light_lava_fragment.txt");
	/*shaderProgramTexture.init("shaders/vertex_shader.txt", "shaders/fragment_shader_texture.txt");
	shaderProgram2Texture.init("shaders/vertex_shader.txt", "shaders/fragment_shader_2texture.txt");*/
	player.init();
	
	player.sizeTitle = sizeTitle;
	player.sizeLine = sizePathway;
	for (int i = 0; i< sizeTitle; i++)
	{
		Square* square = new Square();
		square->id = i;
		vectorSquare.push_back(square);
	}

	for (int i = 0; i < vectorSquare.size(); i++)
	{
		int coordZ = i / 3;
		int coordX = i - coordZ * 3;
		vectorSquare[i]->position = { -1.0f + 1.0f * coordX, 0.0f, -1.0f * coordZ };
	}

	for (int i = 0; i < vectorSquare.size(); i++)
	{
		if (i % 15 == 0 || i % 15 == 2)
		{
			LightCube* lightCube = new LightCube();
			lightCube->generate(vectorSquare, i);
			vectorLightCube.push_back(lightCube);
		}
	}
	cout << vectorLightCube.size() << endl;

	generate();
}

void Pathway::generate()
{	
	for (int i = 9; i < vectorSquare.size(); i++)
	{
		if(vectorSquare[i]->type == Type::None && mSizeTrain[i / 3] != 2)
			if (uid(gen) == 1)
			{
				int size = ulong(gen);
				int future = 0;
				//проходим по столбцу вверх на заген. длинну
				for (int j = 0; j < size; j++)
				{
					int current = i + 3 * j;
					if (current < sizeTitle)
					{	
						if (vectorSquare[current]->type == Type::Safety)
						{
							//flag = true;
							size = j;
							break;
						}
						vectorSquare[current]->type = Type::Train;
						mSizeTrain[current / 3] += 1;   ////////////////
					}
					else
					{
						vectorSquare[current - sizeTitle]->futureType = Type::Train; //////
						//mSizeTrain[current] ++;
						future++;
					}
				}
				// после последннего элемента присваиваем тип безопасной €чейки
				int safeT;
				bool flag = false;
				if (i + 3 * size < sizeTitle) {
					safeT = i + 3 * size;
					flag = true;
					setSafety(safeT, flag);
					flag = (safeT + 3 < sizeTitle ? true : false);
					safeT = (safeT + 3 < sizeTitle ? safeT + 3 : safeT + 3 - sizeTitle);
					setSafety(safeT, flag);
				}
				else {
					safeT = i + 3 * size - sizeTitle;
					flag = false;
					setSafety(safeT, flag);
					safeT += 3;
					//safeT = (safeT + 3 < sizeTitle ? safeT + 3 : safeT + 3 - sizeTitle);
					setSafety(safeT, flag);
				}
			}
	}
	drawVector(0);
}

void Pathway::generateMove(int key)
{
	if (key % 3 == 0)
	{
		mSizeTrain[key / 3] = 0;
		for (int i = 0; i < 3; i++)
		{
			if (vectorSquare[key + i]->futureType == Type::Train)
				mSizeTrain[key / 3]++;
		}
	}

	vectorSquare[key]->type = vectorSquare[key]->futureType;
	vectorSquare[key]->futureType = Type::None;
	if (vectorSquare[key]->type == Type::None && mSizeTrain[key / 3] < 2)
	{
		if (uid(gen) == 1)
		{
			int size = ulong(gen);
			int future = 0;
			vectorSquare[key]->type = Type::Train;
			mSizeTrain[key / 3] += 1;
			//проходим по столбцу вверх на заген. длинну
			for (int j = 1; j < size; j++)
			{
				int current = key + 3 * j;				
				if (current >= sizeTitle)
				{
					if (vectorSquare[current - sizeTitle]->futureType == Type::Safety)
					{
						size = j;
						break;
					}
					vectorSquare[current - sizeTitle]->futureType = Type::Train;
				}
				else
				{
					if (vectorSquare[current]->futureType == Type::Safety)
					{
						size = j;
						break;
					}
					vectorSquare[current]->futureType = Type::Train;
				}
			}

			int safeT = (key + 3 * size < sizeTitle ? key + 3 * size : key + 3 * size - sizeTitle);
			setSafety(safeT, false);
			safeT = (safeT + 3 < sizeTitle ? safeT + 3 : safeT + 3 - sizeTitle);
			setSafety(safeT, false);

		}
	}
}

void Pathway::setSafety(int key, bool flag)
{
	if (flag)
	{
		key = key / 3 * 3;
		vectorSquare[key]->type = Type::Safety;
		vectorSquare[key + 1]->type = Type::Safety;
		vectorSquare[key + 2]->type = Type::Safety;
	}
	else
	{
		key = key / 3 * 3;
		vectorSquare[key]->futureType = Type::Safety;
		vectorSquare[key + 1]->futureType = Type::Safety;
		vectorSquare[key + 2]->futureType = Type::Safety;
	}
}

void Pathway::draw()
{
	shaderProgram.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Square));
	shaderProgram.setInt("material.diffuse1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Cube));
	shaderProgram.setInt("material.diffuse2", 1);

	shaderProgram.setVec3("material.specular", { 1.0f, 1.0f, 1.0f });
	shaderProgram.setFloat("material.shininess", 32.0f);

	glm::mat4 view;
	view = Camera::camera.GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(Camera::camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, Long);
	shaderProgram.setMat4("view", view);
	shaderProgram.setMat4("projection", projection);

	shaderProgram.setVec3("veiwPos", Camera::camera.Position);

	glm::vec3 diffuseColor = glm::vec3(1.0f) * glm::vec3(0.5f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.5f);
	glm::vec3 specularColor = glm::vec3(1.0f) * glm::vec3(0.5f);

	for (int i = 0; i < vectorLightCube.size(); i++)
	{
		string name = "pointLights[" + to_string(i) + "].";
		shaderProgram.setVec3(name + "position", vectorLightCube[i]->position);
		shaderProgram.setVec3(name + "ambient", ambientColor);
		shaderProgram.setVec3(name + "diffuse", diffuseColor);
		shaderProgram.setVec3(name + "specular", specularColor);

		shaderProgram.setFloat(name + "constant", 1.0f);
		shaderProgram.setFloat(name + "linear", 0.35);
		shaderProgram.setFloat(name + "quadratic", 0.44);
	}

	//diffuseColor = glm::vec3(207 / 255, 16 / 255, 32 / 255) * glm::vec3(0.2f); // decrease the influence
	GLfloat x = (GLfloat)207 / 255;
	GLfloat y = (GLfloat)16 / 255;
	GLfloat z = (GLfloat)32 / 255;
	diffuseColor = glm::vec3(x, y, z) * glm::vec3(0.5f);
	ambientColor = diffuseColor * glm::vec3(0.3f);
	specularColor = glm::vec3(1.0f) * glm::vec3(0.05f);

	int k = 0;
	for (int i = 0; i < vectorSquare.size(); i++)
	{
		if (i % 3 == 0)
		{
			glm::vec3 pos = vectorSquare[i]->position;
			pos.x = pos.x - 1.0f;
			string name = "pointLava[" + to_string(k) + "].";
			shaderProgram.setVec3(name + "position", pos);
			shaderProgram.setVec3(name + "ambient", ambientColor);
			shaderProgram.setVec3(name + "diffuse", diffuseColor);
			shaderProgram.setVec3(name + "specular", specularColor);

			shaderProgram.setFloat(name + "constant", 1.0f);
			shaderProgram.setFloat(name + "linear", 0.9);
			shaderProgram.setFloat(name + "quadratic", 2.4);
			k++;
		}
		if (i % 3 == 2)
		{
			glm::vec3 pos = vectorSquare[i]->position;
			pos.x = pos.x + 1.0f;
			string name = "pointLava[" + to_string(k) + "].";
			shaderProgram.setVec3(name + "position", pos);
			shaderProgram.setVec3(name + "ambient", ambientColor);
			shaderProgram.setVec3(name + "diffuse", diffuseColor);
			shaderProgram.setVec3(name + "specular", specularColor);

			shaderProgram.setFloat(name + "constant", 1.0f);
			shaderProgram.setFloat(name + "linear", 0.9);
			shaderProgram.setFloat(name + "quadratic", 2.4);
			k++;
		}
	}

	drawTile();
	drawCube();
	drawWalls();	
	player.draw(shaderProgram);
	drawLights();
	player.collision(vectorSquare, currentLine);
}

void Pathway::drawTile()
{
	shaderProgram.setFloat("material.key", 0.0f);
	GLfloat aceel = glfwGetTime() * 0.02;
	aceel = (aceel > 1.5f ? 1.5f : aceel);
	GLfloat speed = (player.life ? 3.0f + aceel : 0.0f);
	GLfloat velocity = speed * Camera::camera.deltaTime;
	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Square));
	for (int i = 0; i < vectorSquare.size(); i++)
	{
		//shaderProgram.setVec3("colorObject", vectorSquare[i]->color);
		glm::mat4 model;
		vectorSquare[i]->position += directive * velocity; // перемещение
		if (vectorSquare[i]->position.z >= 1.0f)
		{
			// смещаем в конец, если строка перешла границу
			currentLine = vectorSquare[i]->id / 3;
			int bias = ceil((double)vectorSquare.size() / 3);
			vectorSquare[i]->position.z -= bias * 1.0f;
			generateMove(i);
			//drawVector(i);

		}
		model = glm::translate(model, vectorSquare[i]->position);
		shaderProgram.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6); ///
	}
	glBindVertexArray(0);
}

void Pathway::drawCube()
{
	shaderProgram.setFloat("material.key", 1.0f);

	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Cube));
	for (int i = 0; i < vectorSquare.size(); i++)
	{
		if (vectorSquare[i]->type == Type::Train)
		{
			//shaderProgramTexture.setVec3("colorObject", vectorSquare[i]->colorCube);
			glm::mat4 model1;
			glm::vec3 pos = vectorSquare[i]->position;
			pos += glm::vec3(0.0f, 0.5f, 0.0f);
			model1 = glm::translate(model1, pos);
			shaderProgram.setMat4("model", model1);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glm::mat4 model2;
			pos += glm::vec3(0.0f, 1.0f, 0.0f);
			model2 = glm::translate(model2, pos);
			shaderProgram.setMat4("model", model2);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	glBindVertexArray(0);
}

void Pathway::drawWalls()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Lava));
	glUniform1i(glGetUniformLocation(shaderProgram.Program, "material.diffuse1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Stones));
	glUniform1i(glGetUniformLocation(shaderProgram.Program, "material.diffuse2"), 1);

	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Square));

	GLfloat xangle = -0.5f - sqrt(2) / 4;
	GLfloat xsheer = -0.5f - sqrt(2) / 2;
	GLfloat yangle = sqrt(2) / 4;

	for (int i = 0; i < vectorSquare.size(); i++)
	{
		if (i % 3 == 0)
		{
			/*shaderProgram.setFloat("material.key", 0.0f);
			glm::mat4 model_1;
			glm::vec3 pos_1(vectorSquare[i]->position.x - 1.0f, 0, vectorSquare[i]->position.z);
			model_1 = glm::translate(model_1, pos_1);
			shaderProgram.setMat4("model", model_1);
			glDrawArrays(GL_TRIANGLES, 0, 6);*/
			/////////
			shaderProgram.setFloat("material.key", 1.0f);
			glm::mat4 model_2;
			glm::vec3 pos_2(vectorSquare[i]->position.x - 1.0f + xangle, yangle, vectorSquare[i]->position.z);
			model_2 = glm::translate(model_2, pos_2);
			model_2 = glm::rotate(model_2, -45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_2);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			///////// 			
			glm::mat4 model_3;
			glm::vec3 pos_3(vectorSquare[i]->position.x - 1.0f + xsheer, yangle*2 + 0.5f, vectorSquare[i]->position.z);
			model_3 = glm::translate(model_3, pos_3);
			model_3 = glm::rotate(model_3, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_3);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////			
			glm::mat4 model_4;
			glm::vec3 pos_4(vectorSquare[i]->position.x - 1.0f + xsheer, yangle * 2 + 1.5f, vectorSquare[i]->position.z);
			model_4 = glm::translate(model_4, pos_4);
			model_4 = glm::rotate(model_4, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_4);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////		
			glm::mat4 model_5;
			glm::vec3 pos_5(vectorSquare[i]->position.x - 1.0f + xangle, yangle * 3 + 2.0f, vectorSquare[i]->position.z);
			model_5 = glm::translate(model_5, pos_5);
			model_5 = glm::rotate(model_5, -135.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_5);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			glm::mat4 model_6;
			glm::vec3 pos_6(vectorSquare[i]->position.x - 1.0f, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_6 = glm::translate(model_6, pos_6);
			model_6 = glm::rotate(model_6, -180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_6);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			glm::mat4 model_7;
			glm::vec3 pos_7(vectorSquare[i]->position.x, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_7 = glm::translate(model_7, pos_7);
			model_7 = glm::rotate(model_7, -180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_7);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			glm::mat4 model_8;
			glm::vec3 pos_8(vectorSquare[i]->position.x + 1.0f, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_8 = glm::translate(model_8, pos_8);
			model_8 = glm::rotate(model_8, -180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_8);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (i % 3 == 2)
		{
			/*shaderProgram.setFloat("material.key", 0.0f);
			glm::mat4 model_1;
			glm::vec3 pos_1(vectorSquare[i]->position.x + 1.0f, 0, vectorSquare[i]->position.z);
			model_1 = glm::translate(model_1, pos_1);
			shaderProgram.setMat4("model", model_1);
			glDrawArrays(GL_TRIANGLES, 0, 6);*/
			/////////
			shaderProgram.setFloat("material.key", 1.0f);
			glm::mat4 model_2;
			glm::vec3 pos_2(vectorSquare[i]->position.x + 1.0f - xangle, yangle, vectorSquare[i]->position.z);
			model_2 = glm::translate(model_2, pos_2);
			model_2 = glm::rotate(model_2, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_2);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////			
			glm::mat4 model_3;
			glm::vec3 pos_3(vectorSquare[i]->position.x + 1.0f - xsheer, yangle * 2 + 0.5f, vectorSquare[i]->position.z);
			model_3 = glm::translate(model_3, pos_3);
			model_3 = glm::rotate(model_3, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_3);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////			
			glm::mat4 model_4;
			glm::vec3 pos_4(vectorSquare[i]->position.x + 1.0f - xsheer, yangle * 2 + 1.5f, vectorSquare[i]->position.z);
			model_4 = glm::translate(model_4, pos_4);
			model_4 = glm::rotate(model_4, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_4);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////		
			glm::mat4 model_5;
			glm::vec3 pos_5(vectorSquare[i]->position.x + 1.0f - xangle, yangle * 3 + 2.0f, vectorSquare[i]->position.z);
			model_5 = glm::translate(model_5, pos_5);
			model_5 = glm::rotate(model_5, 135.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_5);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			glm::mat4 model_6;
			glm::vec3 pos_6(vectorSquare[i]->position.x + 1.0f, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_6 = glm::translate(model_6, pos_6);
			model_6 = glm::rotate(model_6, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_6);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			glm::mat4 model_7;
			glm::vec3 pos_7(vectorSquare[i]->position.x, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_7 = glm::translate(model_7, pos_7);
			model_7 = glm::rotate(model_7, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shaderProgram.setMat4("model", model_7);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			/////////
			/*glm::mat4 model_8;
			glm::vec3 pos_8(vectorSquare[i]->position.x + 1.0f, yangle * 4 + 2.0f, vectorSquare[i]->position.z);
			model_8 = glm::translate(model_8, pos_8);
			shaderProgram2Texture.setMat4("model", model_8);
			glDrawArrays(GL_TRIANGLES, 0, 6);*/
		}
	}
	glBindVertexArray(0);
}

void Pathway::drawLights()
{
	shaderProgramLamp.use();
	glm::mat4 view;
	view = Camera::camera.GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(Camera::camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, Long);
	// Get the uniform locations
	shaderProgramLamp.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	shaderProgramLamp.setMat4("view", view);
	shaderProgramLamp.setMat4("projection", projection);
	//shaderProgramLamp.setVec3("colorObject", glm::vec3(1.0f, 1.0f, 1.0f));

	/*GLfloat xangle = -0.5f - sqrt(2) / 4;
	GLfloat xsheer = -0.5f - sqrt(2) / 2;
	GLfloat yangle = sqrt(2) / 4;*/
	GLfloat rCube = 0.2f;
	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Cube));
	for (int i = 0; i < vectorLightCube.size(); i++)
	{				
		int _id = vectorLightCube[i]->id;
		vectorLightCube[i]->position.z = vectorSquare[_id]->position.z;
		glm::mat4 model;
		model = glm::translate(model, vectorLightCube[i]->position);
		model = glm::scale(model, glm::vec3(rCube));
		shaderProgramLamp.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);		
	}
	glBindVertexArray(0);

	shaderProgramLava.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Lava));
	glUniform1i(glGetUniformLocation(shaderProgramLava.Program, "ourTexture"), 0);

	shaderProgramLava.setVec3("lightColor", glm::vec3(207/255, 16/255, 32/255));

	shaderProgramLava.setMat4("view", view);
	shaderProgramLava.setMat4("projection", projection);

	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Square));
	for (int i = 0; i < vectorSquare.size(); i++)
	{
		if (i % 3 == 0)
		{
			glm::mat4 model_1;
			glm::vec3 pos_1(vectorSquare[i]->position.x - 1.0f, 0, vectorSquare[i]->position.z);
			model_1 = glm::translate(model_1, pos_1);
			shaderProgramLava.setMat4("model", model_1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (i % 3 == 2)
		{
			glm::mat4 model_1;
			glm::vec3 pos_1(vectorSquare[i]->position.x + 1.0f, 0, vectorSquare[i]->position.z);
			model_1 = glm::translate(model_1, pos_1);
			shaderProgramLava.setMat4("model", model_1);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	glBindVertexArray(0);
}

void Pathway::drawVector(int key)
{
	if (key % 3 == 0)
	{
		for (int i = key; i < vectorSquare.size() + key; i++)
		{
			if (i < vectorSquare.size())
				cout << (int)vectorSquare[i]->type << " ";
			else
				cout << (int)vectorSquare[i - vectorSquare.size()]->type << " ";

			if ((i + 1) % 3 == 0)
			{
				if (i < vectorSquare.size())
					cout << "  " << mSizeTrain[i / 3] << endl;
				else
					cout << "  " << mSizeTrain[(i - vectorSquare.size()) / 3] << endl;
				
			}
		}
		cout << endl;
	}
}
