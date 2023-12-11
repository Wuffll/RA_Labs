#include "ParticleContainer.h"

ParticleContainer::ParticleContainer(Shader& shader, const std::vector<Texture>& textures, Camera& camera, const unsigned int& count, const glm::vec3& sourcePosition)
	:
	mShader(&shader),
	mTextures(textures),
	mViewerCamera(&camera),
	mSourcePosition(sourcePosition)
{
	glm::vec3 particlePos = sourcePosition;
	for (int i = 0; i < count; i++)
	{
		mParticles.push_back(new Panel(shader, textures, camera));

		// Calculating new position and life duration
		particlePos.x += (rand() % 11 - 5) / 5.0f;
		particlePos.y += (rand() % 3 - 1) / 5.0f;
		particlePos.z += -(rand() % 21 + 1.0f) / 5.0f;
		mParticles[i]->GetTransform().SetPosition(particlePos);
		mParticles[i]->SetLifeDuration(rand() % 11 + 10.0f);

		particlePos = mSourcePosition;
	}
}

void ParticleContainer::AddParticle()
{
	glm::vec3 newParticlePos = mSourcePosition;
	mParticles.push_back(new Panel(*mShader, mTextures, *mViewerCamera));

	newParticlePos.x += (rand() % 11 - 5) / 5.0f;
	newParticlePos.y += (rand() % 3 - 1) / 5.0f;
	newParticlePos.z += -(rand() % 11) / 5.0f;

	mParticles[mParticles.size() - 1]->GetTransform().SetPosition(newParticlePos);
	mParticles[mParticles.size() - 1]->SetLifeDuration(rand() % 11 + 5.0f);
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
	glm::vec3 newParticlePos = mSourcePosition;

	for (int i = 0; i < mParticles.size(); i++)
	{
		auto& particle = mParticles[i];
		if (particle->IsDead())
		{
			delete particle;
			mParticles.erase(mParticles.begin() + i);

			AddParticle();
		}
		else
		{
			particle->Draw();
		}
	}
}