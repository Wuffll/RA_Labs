#include "ParticleContainer.h"

ParticleContainer::ParticleContainer(Shader& shader, const std::vector<Texture>& textures, Camera& camera, const unsigned int& count)
{
	for (int i = 0; i < count; i++)
	{
		mParticles.push_back(new Panel(shader, textures, camera));
		mParticles[i]->GetTransform().SetPosition({ i, 0.0f, -rand() % 8 - 2 });
	}
}

void ParticleContainer::Update(const float& timeElapsed)
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i]->Update(timeElapsed);
	}
}

void ParticleContainer::Draw()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		auto& particle = mParticles[i];
		if (particle->IsDead())
		{
			// delete from array; create new
		}
		else
		{
			particle->Draw();
		}
	}
}