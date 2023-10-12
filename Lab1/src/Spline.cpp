#include "Spline.h"

CubicBSpline::CubicBSpline(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate)
	:
	mControlPoints(controlPoints),
	mSampleRate(sampleRate)
{
	FillSplinePoints(controlPoints, sampleRate);
}

CubicBSpline::~CubicBSpline()
{
}

const std::vector<glm::vec3>& CubicBSpline::GetSplinePoints() const
{
	return mSplinePoints;
}

void CubicBSpline::FillSplinePoints(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate)
{
	mSplinePoints.reserve(sampleRate);
	
	// TODO
}

void CubicBSpline::Draw()
{
	// TODO
}