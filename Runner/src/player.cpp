#include "..\include\player.h"

Player::Player() : right(false), left(false), currentColumn(0), radius(0.3f), life(false)
{
	position = { 0.0f, radius, -1.0f };
	color = { 0.0f, 1.0f, 0.0f };
	Camera::camera.directVec = Camera::camera.Position - position;
}

void Player::init()
{
	shaderProgramTextrue.init("shaders/vertex_shader.txt", "shaders/fragment_shader_texture.txt");
}

void Player::draw()
{
	shaderProgramTextrue.use();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Sphere));
	glUniform1i(glGetUniformLocation(shaderProgramTextrue.Program, "ourTexture"), 0);

	glm::mat4 view;
	view = Camera::camera.GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(Camera::camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	shaderProgramTextrue.setMat4("view", view);
	shaderProgramTextrue.setMat4("projection", projection);
	shaderProgramTextrue.setMat4("model", move());

	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Sphere));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, BufferVertex::bufferVertex.sphere->GetIndexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Player::draw(Shader& shader)
{
	//shaderProgramTextrue.use();

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Sphere));
	glUniform1i(glGetUniformLocation(shaderProgramTextrue.Program, "ourTexture"), 0);*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BufferVertex::bufferVertex.getTexture(Figure::Sphere));
	shader.setInt("material.diffuse1", 0);
	shader.setFloat("material.key", 0.0f);
	shader.setMat4("model", move());

	glBindVertexArray(BufferVertex::bufferVertex.getVAO((int)Figure::Sphere));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, BufferVertex::bufferVertex.sphere->GetIndexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//cout << glfwGetTime() << endl;

	//glBindTexture(GL_TEXTURE_2D, 0);
}

glm::mat4 Player::move()
{
	glm::vec3 directRight(1.0f, 0.0f, 0.0f);
	GLfloat speed = 6.0f;
	GLfloat velocity = speed * Camera::camera.deltaTime;
	glm::mat4 model;
	GLfloat deltaPos = currentColumn - position.x;
	if (deltaPos > 0)
	{
		position += directRight * velocity;
		if (position.x > currentColumn) position.x = currentColumn;
		model = glm::translate(model, position);
		model = glm::rotate(model, (GLfloat)glfwGetTime() * -80.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//glm::vec3 rotateVec = directVec;
		//rotateVec.x = sin(0.5);
		//rotateVec.z = cos(0.5);
		//Camera::camera.Position = this->position + rotateVec;
		Camera::camera.Position.x = position.x;
		return model;
	}
	if (deltaPos < 0)
	{
		position -= directRight * velocity;
		if (position.x < currentColumn) position.x = currentColumn;
		model = glm::translate(model, position);
		model = glm::rotate(model, (GLfloat)glfwGetTime() * -80.0f, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		/*Camera::camera.Position = this->position + directVec;*/
		Camera::camera.Position.x = position.x;
		return model;
	}
	model = glm::translate(model, position);
	model = glm::rotate(model, (GLfloat)glfwGetTime() * -80.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	//Camera::camera.Position = this->position + directVec;
	return model;
}

void Player::collision(vector<class Square*> vector, int _current)
{
	_current = (_current + 1 >= this->sizeLine ? 0 : _current + 1);
	int current1 = (_current + 1 >= this->sizeLine ? 0 : _current + 1); // строчки, которые могут быть задействованы
	int current2 = (current1 + 1 >= this->sizeLine ? 0 : current1 + 1);
	GLfloat size = 0.5f;
	int idX = round(this->position.x - this->radius) + 1; // id текущего столбца
	int idY; //id текущей строки, получаем через равенство ниже
	if (vector[current1 * 3]->position.z - size < this->position.z - this->radius + 0.1f) 
		idY = current1;
	else
		idY = current2;

	int id = (idX + idY * 3 < sizeTitle ? idX + idY * 3 : idX + idY * 3 - sizeTitle);

	if (vector[id]->type == Type::Train) // проверяем по id тип текущего объекта
	{
		life = false;
		return;
	}

	idX = round(this->position.x + this->radius) + 1;
	id = (idX + idY * 3 < sizeTitle ? idX + idY * 3 : idX + idY * 3 - sizeTitle);

	if (vector[id]->type == Type::Train)
	{
		life = false;
		return;
	}

	idX = round(this->position.x - this->radius) + 1;

	if (vector[current1 * 3]->position.z - size < this->position.z + this->radius - 0.1f)
		idY = current1;
	else
		idY = current2;

	id = (idX + idY * 3 < sizeTitle ? idX + idY * 3 : idX + idY * 3 - sizeTitle);

	if (vector[id]->type == Type::Train)
	{
		life = false;
		//cout << "3. pos vec: " << vector[current1 * 3]->position.z - size << "pos sphere: " << this->position.z + this->radius << endl;
		return;
	}

	idX = round(this->position.x + this->radius) + 1;
	id = (idX + idY * 3 < sizeTitle ? idX + idY * 3 : idX + idY * 3 - sizeTitle);

	if (vector[id]->type == Type::Train)
	{
		life = false;
		//cout << "4. pos vec: " << vector[current1 * 3]->position.z - size << "pos sphere: " << this->position.z - this->radius << endl;
		return;
	}
}

int Player::getIndex(GLfloat x, GLfloat z)
{
	GLfloat i = round(this->position.x) + 1;
	GLfloat j = round(this->position.z);
	int index = i + 3 * j;
	return index;
}
