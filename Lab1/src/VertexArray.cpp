#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mRendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (void*)(offset));

		offset += e.count * VertexBufferElement::SizeOfDataType(e.type);
	}

	ib.Bind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(mRendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
