#include "Shader.h"

#include <fstream>

Shader::Shader()
{
}

Shader::Shader(const std::string& filePath)
{
	Init(filePath);
}

void Shader::Init(const std::string& filePath)
{
	
}

ShaderProgramSource Shader::ReadShaderFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
		throw false && "File was not able to be opened!";


	ShaderType type = ShaderType::UNDEFINED;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("VERT") != std::string::npos)
				type = ShaderType::VERT;
			if (line.find("FRAG") != std::string::npos)
				type = ShaderType::FRAG;
			if (line.find("GEOM") != std::string::npos)
				type = ShaderType::GEOM;
		}
	}
}
