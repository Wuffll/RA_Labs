#include "IndexBuffer.h"

#include <GL/glew.h>

#include "Debug.h"

#define INITIAL_BUFFER_SIZE 32 * 1024 * 1024; // 32 MB in bytes

unsigned int IndexBuffer::boundIBO = 0;

IndexBuffer::IndexBuffer()
	:
	mUsage(GL_STATIC_DRAW),
	mCount(0)
{
	glGenBuffers(1, &mRendererID);

	Debug::Print("IndexBuffer created without any data! (mRendererID = " + STRING(mRendererID) + ")");
}

IndexBuffer::IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage)
	:
	mUsage(GL_STATIC_DRAW),
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
	AdjustBufferSize(count * sizeof(unsigned int), usage);

	InsertDataWithOffset(data, count, 0);

	mBufferSize = count * sizeof(unsigned int);

	if (mCount == 0)
	{
		this->mCount = count;
	}
}

void IndexBuffer::InsertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset)
{
	size_t size = count * sizeof(unsigned int);

	Bind();
	AdjustBufferSize(offset + size, mUsage);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);

	mBufferSize = (offset + size > mBufferSize) ? offset + size : mBufferSize;
	mCount = ((offset / sizeof(unsigned int)) + count > mCount) ? (offset / sizeof(unsigned int)) + count : mCount;
}

void IndexBuffer::Bind() const
{
	if (mCount == 0)
	{
		Debug::Print("Index buffer " + std::to_string(mRendererID) + " is not initialized! (count = 0)");
	}

	/*
	if (mRendererID == boundIBO)
		return;
	*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	boundIBO = mRendererID;
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::AdjustBufferSize(const unsigned int& newSize, const unsigned int& usage)
{
	bool sizeChanged = false;
	if (mBufferCapacity == 0)
	{
		mBufferCapacity = INITIAL_BUFFER_SIZE;
		sizeChanged = true;
	}

	while (mBufferCapacity < newSize)
	{
		mBufferCapacity += mBufferCapacity;
		sizeChanged = true;
	}

	if (sizeChanged)
	{
		Bind();

		void* data = nullptr;

		if (mBufferSize != 0)
		{
			data = malloc(mBufferSize);
			glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, mBufferSize, data);
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mBufferCapacity, data, usage);

		delete data;
	}
}

const unsigned int& IndexBuffer::GetIndicesCount() const
{
	return mCount;
}

const unsigned int& IndexBuffer::GetBufferSize() const
{
	return mBufferSize;
}
