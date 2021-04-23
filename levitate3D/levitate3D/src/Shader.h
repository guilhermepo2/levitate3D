#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ProgramID;

	Shader(const char* VertexPath, const char* FragmentPath);
	void Use() { glUseProgram(ProgramID); }

	// TODO: Bad code repetition here! templates are for this lol
	template<typename T>
	void Set(const std::string& Name, T Value) const { glUniform1i(glGetUniformLocation(ProgramID, Name.c_str()), Value); }

	void SetBool(const std::string& Name, bool Value) const { glUniform1i(glGetUniformLocation(ProgramID, Name.c_str()), (int)Value); }
	void SetInt(const std::string& Name, int Value) const { glUniform1i(glGetUniformLocation(ProgramID, Name.c_str()), Value); }
	void SetFloat(const std::string& Name, float Value) const { glUniform1f(glGetUniformLocation(ProgramID, Name.c_str()), Value); }

	void SetVec3(const std::string& Name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(ProgramID, Name.c_str()), x, y, z);
	}
};

Shader::Shader(const char* VertexPath, const char* FragmentPath) {
	std::string VertexCode;
	std::string FragmentCode;
	std::ifstream VertexShaderFile;
	std::ifstream FragmentShaderFile;

	// TODO: I don't really like throwing exceptions here...
	VertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	FragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		VertexShaderFile.open(VertexPath);
		FragmentShaderFile.open(FragmentPath);
		std::stringstream VertexShaderStream, FragmentShaderStream;
		VertexShaderStream << VertexShaderFile.rdbuf();
		FragmentShaderStream << FragmentShaderFile.rdbuf();
		VertexShaderFile.close();
		FragmentShaderFile.close();

		VertexCode = VertexShaderStream.str();
		FragmentCode = FragmentShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = VertexCode.c_str();
	const char* fShaderCode = FragmentCode.c_str();

	// compiling shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::vERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADEr::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
	}

	// Shader program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex);
	glAttachShader(ProgramID, fragment);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ProgramID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_ERROR: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}