#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../Dependencies/include/glad/glad.h"

#include "./Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	// Part 1: Get code from vertex and fragment files and put them in const char form.
	const char* vertexCode;
	const char* fragmentCode;
	try {
		// vertex shit
		std::ifstream vertex(vertexPath);
		std::stringstream vertexStream;
		vertexStream << vertex.rdbuf();
		vertex.close();
		vertexCode = vertexStream.str().c_str();

		// fragment shit
		std::ifstream fragment(vertexPath);
		std::stringstream fragmentStream;
		fragmentStream << fragment.rdbuf();
		fragment.close();
		fragmentCode = fragmentStream.str().c_str();

	} catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_ERROR" << e.what() << std::endl;
	}
	// END OF PART 1

	// Part 2: Create shader program from the extracted vertex and fragment shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

		// Turning vertex into a shader with unique id
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
			// Checking if compiling is successful
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

		// Turning fragment into a shader with unique id
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
			// Checking if compiling is successful
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

		// Creating shader program with the vertex and fragment shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
		// Check if linking is successful
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// END OF PART 2

	// Can delete shaders since no more use for them
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// DONE!!!
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}