#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <fstream>

Shader::Shader()
{
}

Shader::Shader(const std::string& filePath)
	:
	mFilePath(filePath)
{
	Init(filePath);
}

unsigned int Shader::GetShaderId()
{
	return mShaderId;
}

Shader::~Shader()
{
	glDeleteProgram(mShaderId);
}

void Shader::Init(const std::string& filePath)
{
	ShaderProgramSource source = ReadShaderFile(filePath);

	unsigned int program = glCreateProgram();
	unsigned int shader;
	std::vector<unsigned int> shaders{};

	if (source.Vertex.size() != 0)
	{
		shader = CompileShader(GL_VERTEX_SHADER, source.Vertex);
		glAttachShader(program, shader);
		shaders.push_back(shader);
	}

	if (source.Fragment.size() != 0)
	{
		shader = CompileShader(GL_FRAGMENT_SHADER, source.Fragment);
		glAttachShader(program, shader);
		shaders.push_back(shader);
	}

	if (source.Geometry.size() != 0)
	{
		shader = CompileShader(GL_GEOMETRY_SHADER, source.Geometry);
		glAttachShader(program, shader);
		shaders.push_back(shader);
	}

	glLinkProgram(program);
	glValidateProgram(program);

	for (auto& s : shaders)
	{
		glDeleteShader(s);
	}

	mShaderId = program;
}

ShaderProgramSource Shader::ReadShaderFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
		throw false && "File was not able to be opened!";


	ShaderType type = ShaderType::UNDEFINED;
	ShaderProgramSource source;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("VERT") != std::string::npos)
				type = ShaderType::VERT;
			else if (line.find("FRAG") != std::string::npos)
				type = ShaderType::FRAG;
			else if (line.find("GEOM") != std::string::npos)
				type = ShaderType::GEOM;
		}
		else
		{
			switch (type)
			{
				case VERT:
					source.Vertex.append(line + "\n");
					break;
				case FRAG:
					source.Fragment.append(line + "\n");
					break;
				case GEOM:
					source.Geometry.append(line + "\n");
					break;
			}
		}
	}

	return source;
}

unsigned int Shader::CompileShader(unsigned int shaderType, const std::string& source)
{
	unsigned int id = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result, length;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, &msg[0]);

		std::cout << "Failed to compile shader! (shader = " << shaderType << ")" << std::endl;
		std::cout << msg << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}
