#pragma once

#include <vector>

#include "Panel.h"

class ParticleContainer
{
public:

	ParticleContainer(Shader& shader, const std::vector<Texture>& textures, Camera& camera, const unsigned int& count, const glm::vec3& sourcePosition);

	void AddParticle();

	void Update(const float& timeElapsed);
	void Draw();

private:

	std::vector<Panel*> mParticles;
	glm::vec3 mSourcePosition;

	Shader* mShader;
	std::vector<Texture> mTextures;
	Camera* mViewerCamera;

};