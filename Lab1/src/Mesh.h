#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <limits>

#include "VertexArray.h"
#include "Vertex.h"

struct MinMax
{
	double min = std::numeric_limits<double>::max();
	double max = std::numeric_limits<double>::min();
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

	VertexBuffer mVBO;
	IndexBuffer mIBO;

	glm::mat4 mTransformMatrix;

	std::vector<Vertex> mVertices{};
	std::vector<unsigned int> mIndices{};
	std::vector<MinMax> mBoundingBox{};
	const std::string mFilePath;

};