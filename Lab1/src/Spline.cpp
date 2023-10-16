#include "Spline.h"

#include "Debug.h"

CubicBSpline::CubicBSpline(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate)
	:
	mControlPoints(controlPoints),
	mSampleRate(sampleRate),
	mNumOfSegments(controlPoints.size() - 3)
{
	FillSplinePoints(controlPoints, sampleRate);
}

CubicBSpline::~CubicBSpline()
{
}

const std::vector<Vertex>& CubicBSpline::GetSplinePoints() const
{
	return mSplinePoints;
}

void CubicBSpline::FillSplinePoints(const std::vector<glm::vec3>& controlPoints, const unsigned int& sampleRate)
{
	mSplinePoints.reserve(sampleRate);
	
	if (controlPoints.size() < 4)
		Debug::ThrowException("Must have at least 4 control points! (current size = " + std::to_string(controlPoints.size()) + ")");

	int numPointsPerSegment = sampleRate / mNumOfSegments;
	float delta = 1.0f / (numPointsPerSegment - 1);

	for (int i = 1; i <= controlPoints.size() - 3; i++)
	{
		glm::vec4 T{};
		glm::mat4x3 R{ controlPoints[i - 1], controlPoints[i], controlPoints[i + 1], controlPoints[i + 2]};
		glm::mat4 B{ {-1.0f, 3.0f, -3.0f, 1.0f}, {3.0f, -6.0f, 3.0f, 0.0f}, {-3.0f, 0.0f, 3.0f, 0.0f}, {1.0f, 4.0f, 1.0f, 0.0} };
		glm::vec3 opResult;
		int k = 0;
		for (float j = 0.0f; j < 1.0f; j += delta, k++)
		{
			T = {j*j*j, j*j, j, 1};
			opResult = { R * B * (T * (1.0f / 6.0f)) };

			mSplinePoints.push_back({ opResult, {1.0f, 1.0f, 1.0f} });

			std::cout << mSplinePoints[mSplinePoints.size() - 1].pos.x << ", " << mSplinePoints[mSplinePoints.size() - 1].pos.y << ", " << mSplinePoints[mSplinePoints.size() - 1].pos.z << std::endl;
		}
	}
	// TODO
}

void CubicBSpline::Draw()
{
	// TODO
}