#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Transform.h"

class CubicBSpline : public Drawable
{
public:

	CubicBSpline(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate = 1000);
	~CubicBSpline();

	const std::vector<Vertex>& GetSplinePoints() const;

	void FillSplinePoints(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate);

	void Draw() const;
	Transform& GetTransform();

private:

	VertexArray mVArray;
	VertexBuffer mVBuffer;
	IndexBuffer mIBuffer;
	Transform mTransform;
	std::vector<glm::vec3> mControlPoints;
	std::vector<Vertex> mSplinePoints;
	int mNumOfSegments;
	unsigned int mSampleRate;

};