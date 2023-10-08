#pragma once

class VertexBuffer
{
public:
	
	VertexBuffer(const void* data, const unsigned int& size, unsigned int usage);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	unsigned int mRendererID;

};