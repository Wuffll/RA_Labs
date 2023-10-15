#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <limits>

#include "VertexArray.h"

struct MinMax
{
	double min = std::numeric_limits<double>::max();
	double max = std::numeric_limits<double>::min();
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
};

class Mesh
{
public:

	Mesh(const std::string& filePath);
	~Mesh();

	const VertexBuffer& GetVB() const;
	const IndexBuffer& GetIB() const;

	const glm::mat4& GetTransform() const;
	
private:

	//VertexArray& mVAO;
	VertexBuffer mVBO;
	IndexBuffer mIBO;

	glm::mat4 mTransformMatrix;

	std::vector<Vertex> mVertices{};
	std::vector<unsigned int> mIndices{};
	std::vector<MinMax> mBoundingBox{};
	const std::string mFilePath;

};