#pragma once

#include <string>

struct ShaderProgramSource
{
	std::string Vertex{};
	std::string Fragment{};
	std::string Geometry{};
};

enum ShaderType
{
	UNDEFINED = -1,
	VERT = 0,
	FRAG = 1,
	GEOM = 2
};

class Shader
{
public:

	Shader();
	Shader(const std::string& filePath);

private:

	void Init(const std::string& filePath);
	ShaderProgramSource ReadShaderFile(const std::string& filePath);

	unsigned int mShaderId = 0;
	std::string mFilePath{};
};