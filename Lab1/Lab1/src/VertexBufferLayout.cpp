#include "VertexBufferLayout.h"

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
    return mElements;
}

const unsigned int& VertexBufferLayout::GetStride() const
{
    return mStride;
}
