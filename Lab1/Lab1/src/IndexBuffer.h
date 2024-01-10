#pragma once

class IndexBuffer
{
public:

	IndexBuffer();
	IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	~IndexBuffer();

	void FillBuffer(const void* data, const unsigned int& count, const unsigned int& usage);

	void Bind() const;
	void Unbind() const;

	unsigned int GetIndicesCount() const;

private:

	unsigned int mRendererID;
	unsigned int mCount = 0;
};