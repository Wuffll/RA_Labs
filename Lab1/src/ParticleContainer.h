#pragma once

#include <vector>

#include "Panel.h"

class ParticleContainer
{
public:

	ParticleContainer(Shader& shader, const std::vector<Texture>& textures, Camera& camera, const unsigned int& count);

	void Update(const float& timeElapsed);
	void Draw();

private:

	std::vector<Panel*> mParticles;

};