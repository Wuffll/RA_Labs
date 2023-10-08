#include "IndexBuffer.h"

#include <GL/glew.h>

#define INDEX_SIZE sizeof(unsigned int) // for indices, type is *unsigned int*

IndexBuffer::IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int) && sizeof(GLuint) == sizeof(unsigned int));

	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * INDEX_SIZE, data, usage);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mRendererID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
