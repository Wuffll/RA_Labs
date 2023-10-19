#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Transform.h"

class CubicBSpline : public Drawable
{
public:

	CubicBSpline(std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate = 1000);
	~CubicBSpline();

	const std::vector<Vertex>& GetSplinePoints() const;
	const std::vector<glm::mat4>& GetRotationMatrices() const;

	void FillSplinePoints(std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate);

	void Draw() const;
	Transform& GetTransform();

private:

	VertexArray mVArray;
	VertexBuffer mVBuffer;
	IndexBuffer mIBuffer;
	Transform mTransform;
	std::vector<glm::vec3> mControlPoints;
	std::vector<Vertex> mSplinePoints;
	std::vector<Vertex> mTangents;
	std::vector<Vertex> mNormals;
	std::vector<Vertex> mBinormals;
	std::vector<glm::mat4> mRotationMatrices;
	int mNumOfSegments;
	unsigned int mSampleRate;

};