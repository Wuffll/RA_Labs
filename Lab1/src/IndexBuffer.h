#pragma once

class IndexBuffer
{
public:

	IndexBuffer();
	IndexBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	~IndexBuffer();

	void FillBuffer(const void* data, const unsigned int& count, const unsigned int& usage);
	void InsertDataWithOffset(const void* data, const unsigned int& count, const unsigned int& offset);

	void Bind() const;
	void Unbind() const;

	void AdjustBufferSize(const unsigned int& newSize, const unsigned int& usage);

	const unsigned int& GetIndicesCount() const;
	const unsigned int& GetBufferSize() const;


private:

	static unsigned int boundIBO;

	unsigned int mRendererID = 0;
	unsigned int mUsage;

	unsigned int mCount = 0;
	unsigned int mBufferCapacity = 0;
	unsigned int mBufferSize = 0;
};