#include "Renderer.h"

Renderer::Renderer(Shader& shader)
	:
	mShader(shader)
{
}

void Renderer::Draw() const
{
	mShader.Bind();

	for (const auto& obj : mDrawableObjects)
	{
		mShader.SetUniformMatrix4f("model", obj->GetTransform());
		obj->Draw();
	}
}

void Renderer::AddDrawableObject(Drawable& object)
{
	mDrawableObjects.push_back(&object);
}
