#pragma once

class VertexBuffer
{
public:
	
	VertexBuffer();
	VertexBuffer(const void* data, const unsigned int& size, unsigned int usage);
	~VertexBuffer();

	void FillBuffer(const void* data, const unsigned int& size, unsigned int usage);

	const bool& IsInitialized() const;

	const unsigned int& GetRendererID() const;

	void Bind() const;
	void Unbind() const;

private:

	bool mInitialized = false;
	unsigned int mRendererID = 0;

};