#include "VertexBuffer.h"

#include <GL/glew.h>

#include "Debug.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &mRendererID);

	Debug::Print("VertexBuffer created without any data! (mRendererID = " + STRING(mRendererID) + ")");
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
	Debug::Print("Vertex buffer " + std::to_string(mRendererID) + " destroyed!");
	glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::FillBuffer(const void* data, const unsigned int& size, unsigned int usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);

	mInitialized = true;
}

const bool& VertexBuffer::IsInitialized() const
{
	return mInitialized;
}

const unsigned int& VertexBuffer::GetRendererID() const
{
	return mRendererID;
}

void VertexBuffer::Bind() const
{
	if (!mInitialized)
	{
		Debug::Print("Vertex buffer " + std::to_string(mRendererID) + " is uninitialized! (mInitialized = false)");
	}

	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
