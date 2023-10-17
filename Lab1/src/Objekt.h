#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "Drawable.h"
#include "VertexArray.h"
#include "Mesh.h"
#include "Shader.h"

class Objekt : public Drawable
{
public:

	Objekt(const std::string& name, const std::string& filePath, Shader& shader);
	~Objekt();

	void Draw() const;

	const glm::mat4& GetTransform() const;

private:

	std::string mName;
	Mesh mMesh;
	glm::mat4 mTransform{ 1.0f };
	VertexArray mVAO;
	Shader& mShader;

};