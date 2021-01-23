#pragma once

#if !defined(_SHADER_H_)
#define _SHADER_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <string>

using namespace std;

class Shader
{
public:
	GLuint Program;
	//string shaderCodeVertex, shaderCodeFragment;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader();
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void init(const GLchar* vertexPath, const GLchar* fragmentPath);
	void readFromFile(string& shaderCode, const GLchar* patch);
	void checkErrors(GLuint currentShader, string _typeShader);
	void bindCode(GLuint& _currentShader, GLuint _typeShader);
		// activate the shader
		// ------------------------------------------------------------------------
	void use();

	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const;
	
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const;

	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const;

	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w);
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(GLuint shader, std::string type);
};
#endif