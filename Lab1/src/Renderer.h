#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
public:

	Renderer() = default;
	~Renderer() = default;

	void Draw(const VertexArray& vArray, const unsigned int& indicesCount, const Shader& shader) const;

private:



};