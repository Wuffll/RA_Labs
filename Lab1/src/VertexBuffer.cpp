#include "VertexBuffer.h"

#include <GL/glew.h>

#include <iostream>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &mRendererID);
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size, unsigned int usage)
	:
	mInitialized(true)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int));

	glGenBuffers(1, &mRendererID);
	FillBuffer(data, size, usage);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::FillBuffer(const void* data, const unsigned int& size, unsigned int usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	mInitialized = true;
}

void VertexBuffer::Bind() const
{
	if (!mInitialized)
	{
		printf("There is no data in the vertex buffer!\n");
		exit(-1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
