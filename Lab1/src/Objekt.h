#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "Drawable.h"
#include "VertexArray.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

class Objekt : public Drawable
{
public:

	Objekt(const std::string& name, const std::string& filePath, Shader& shader);
	~Objekt();

	void Draw() const;

	Transform& GetTransform();

private:

	std::string mName;
	Mesh mMesh;
	Transform mTransform;
	VertexArray mVAO;
	Shader& mShader;

};