#pragma once

class VertexBuffer
{
public:
	
	VertexBuffer(const void* data, const unsigned int& size, unsigned int usage);
	~VertexBuffer();

	void Bind();
	void Unbind();

private:

	unsigned int mRendererID;

};