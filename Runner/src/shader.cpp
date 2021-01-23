#include "../include/shader.h"
Shader::Shader()
{
}
// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Shader Program
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		// Print linking errors if any
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

//void Shader::init(const GLchar* vertexPath, const GLchar* fragmentPath)
//{
//	// 1. Retrieve the vertex/fragment source code from filePath
//	std::string vertexCode;
//	std::string fragmentCode;
//	std::ifstream vShaderFile;
//	std::ifstream fShaderFile;
//	// ensures ifstream objects can throw exceptions:
//	vShaderFile.exceptions(std::ifstream::badbit);
//	fShaderFile.exceptions(std::ifstream::badbit);
//	try
//	{
//		// Open files
//		vShaderFile.open(vertexPath);
//		fShaderFile.open(fragmentPath);
//		std::stringstream vShaderStream, fShaderStream;
//		// Read file's buffer contents into streams
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//		// close file handlers
//		vShaderFile.close();
//		fShaderFile.close();
//		// Convert stream into string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//	}
//	const GLchar* vShaderCode = vertexCode.c_str();
//	const GLchar* fShaderCode = fragmentCode.c_str();
//	// 2. Compile shaders
//	GLuint vertex, fragment;
//	GLint success;
//	GLchar infoLog[512];
//	// Vertex Shader
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex, 1, &vShaderCode, NULL);
//	glCompileShader(vertex);
//	// Print compile errors if any
//	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	// Fragment Shader
//	fragment = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment, 1, &fShaderCode, NULL);
//	glCompileShader(fragment);
//	// Print compile errors if any
//	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	// Shader Program
//	this->Program = glCreateProgram();
//	glAttachShader(this->Program, vertex);
//	glAttachShader(this->Program, fragment);
//	glLinkProgram(this->Program);
//	// Print linking errors if any
//	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//	// Delete the shaders as they're linked into our program now and no longer necessery
//	glDeleteShader(vertex);
//	glDeleteShader(fragment);
//}
	// activate the shader
	// ------------------------------------------------------------------------

void Shader::init(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	string shaderCodeVertex, shaderCodeFragment;
	readFromFile(shaderCodeVertex, vertexPath);
	readFromFile(shaderCodeFragment, fragmentPath);

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//cout << sizeof(shaderCodeVertex) << endl;
	const GLchar* _shaderCodeVertex = shaderCodeVertex.c_str();
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &_shaderCodeVertex, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const GLchar* _shaderCodeFragment = shaderCodeFragment.c_str();
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &_shaderCodeFragment, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!fragment)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::readFromFile(string& shaderCode, const GLchar* patch)
{
	setlocale(LC_ALL, "rus");
	ifstream fin(patch);
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!" << endl;

	if (fin.is_open())
	{
		std::stringstream sstr;
		sstr << fin.rdbuf();
		shaderCode = sstr.str();
		fin.close();
	}
	else
		cout << "Файл не может быть открыт!" << endl;
}

	void Shader::use()
	{
		glUseProgram(this->Program);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(this->Program, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(this->Program, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(this->Program, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void Shader::setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(this->Program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(this->Program, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void Shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(this->Program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(this->Program, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void Shader::setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(this->Program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(this->Program, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(this->Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(this->Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(this->Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}


	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void Shader::checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
