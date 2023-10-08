#pragma once

class IndexBuffer
{
public:

	IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	~IndexBuffer();

	void Bind();
	void Unbind();

private:

	unsigned int mRendererID;

};