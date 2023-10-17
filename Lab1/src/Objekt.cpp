#include "Objekt.h"

Objekt::Objekt(const std::string& name, const std::string& filePath, Shader& shader)
	:
	mName(name),
	mMesh(filePath),
	mShader(shader),
	mTransform(mMesh.GetTransform())
{
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	mVAO.AddBuffer(mMesh.GetVB(), mMesh.GetIB(), layout);
}

Objekt::~Objekt()
{
}

void Objekt::Draw() const
{
	mShader.Bind();
	mVAO.Bind();

	glDrawElements(GL_TRIANGLES, mMesh.GetIB().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

const glm::mat4& Objekt::GetTransform() const
{
	return mTransform;
}
