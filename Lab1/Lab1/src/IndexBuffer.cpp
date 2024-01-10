#include "IndexBuffer.h"

#include <GL/glew.h>

#include "Debug.h"

#define INDEX_SIZE sizeof(unsigned int) // for indices, type is *unsigned int*

IndexBuffer::IndexBuffer()
	:
	mCount(0)
{
	glGenBuffers(1, &mRendererID);

	Debug::Print("IndexBuffer created without any data! (mRendererID = " + STRING(mRendererID) + ")");
}

IndexBuffer::IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
	:
	mCount(count)
{
	static_assert(sizeof(GLenum) == sizeof(unsigned int) && sizeof(GLuint) == sizeof(unsigned int));

	glGenBuffers(1, &mRendererID);
	FillBuffer(data, count, usage);
}

IndexBuffer::~IndexBuffer()
{
	Debug::Print("Index buffer " + std::to_string(mRendererID) + " destroyed!");
	glDeleteBuffers(1, &mRendererID);
}

void IndexBuffer::FillBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * INDEX_SIZE, data, usage);

	if (mCount == 0)
	{
		this->mCount = count;
	}
}

void IndexBuffer::Bind() const
{
	if (mCount == 0)
	{
		Debug::ThrowException("Index buffer " + std::to_string(mRendererID) + " is not initialized! (count = 0)");
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetIndicesCount() const
{
	return mCount;
}
