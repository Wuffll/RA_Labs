#pragma once

#include <string>

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

class Texture
{
public:

	Texture(const std::string& filePath);

	void Bind() const;

private:

	unsigned int mTextureId;

};

