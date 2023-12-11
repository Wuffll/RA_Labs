#pragma once

#include <vector>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

class Panel
{
public:

	Panel(Shader& shader, const std::vector<Texture>& textures, Camera& camera);

	bool IsDead() const;

	void Update(float elapsedTime);
	void Draw();

	void SetLifeDuration(const float& newLifeDuration);

	Transform& GetTransform();

private:

	std::vector<Texture> mTextures;
	Transform mTransform;
	
	float mAliveTimer = 0.0f;
	float mLifeDuration = 15.0f;
	float mTimeElapsed = 0.0f; // in seconds
	float mAnimationDuration = 0.5f; // in seconds
	char mActiveTexture = 0;

	std::vector<float> mVertexData{};
	std::vector<unsigned int> mIndexData{};

	Shader* mShader;
	Camera* mCamera;
	VertexArray mVAO;
	VertexBuffer mVBO;
	IndexBuffer mIBO;

};