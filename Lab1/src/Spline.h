#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Drawable.h"
#include "Mesh.h"

class CubicBSpline : public Drawable
{
public:

	CubicBSpline(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate = 1000);
	~CubicBSpline();

	const std::vector<Vertex>& GetSplinePoints() const;

	void FillSplinePoints(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate);

	void Draw();

private:

	VertexArray mVArray;
	VertexBuffer mVBuffer;
	IndexBuffer mIBuffer;
	std::vector<glm::vec3> mControlPoints;
	std::vector<Vertex> mSplinePoints;
	int mNumOfSegments;
	unsigned int mSampleRate;

};