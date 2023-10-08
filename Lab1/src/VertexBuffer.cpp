#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size, unsigned int usage)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int));

	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
