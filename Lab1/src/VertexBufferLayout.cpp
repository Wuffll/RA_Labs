#include "VertexBufferLayout.h"

#include "Debug.h"

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
    return mElements;
}

const unsigned int& VertexBufferLayout::GetStride() const
{
    if (!IsInitialized())
        Debug::ThrowException("VertexBufferLayout not initialized!");

    return mStride;
}

const bool VertexBufferLayout::IsInitialized() const
{
    return mElements.size() != 0;
}
