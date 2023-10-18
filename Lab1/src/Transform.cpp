#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const glm::mat4& matrix)
	:
	mMatrix(matrix)
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(const glm::vec3& pos)
{
	glm::vec3 direction = (pos - mPosition) / mScale;
	mMatrix = glm::translate(mMatrix, direction);
	mPosition = pos;
}

void Transform::SetOrientation(const glm::vec3& orientation)
{
	glm::vec3 endOrientation = orientation - mOrientation;

	glm::vec3 axis = { 1.0f, 0.0f, 0.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(endOrientation.x), axis);
	
	axis = { 0.0f, 1.0f, 0.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(endOrientation.y), axis);
	
	axis = { 0.0f, 0.0f, 1.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(endOrientation.z), axis);

	mOrientation = endOrientation;
}

// not sure if this actually works; gotta test
void Transform::ResetScale()
{
	mScale = { 1.0f / mScale.x, 1.0f / mScale.y, 1.0f / mScale.z };
	glm::scale(mMatrix, mScale);
	mScale = { 1.0f, 1.0f, 1.0f };
}

void Transform::Translation(const glm::vec3& translation)
{
	mMatrix = glm::translate(mMatrix, translation / mScale);
	mPosition += translation;
}

void Transform::Rotate(const glm::vec3& rotation)
{
	glm::vec3 axis{ 1.0f, 0.0f, 0.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(rotation.x), axis);

	axis = { 0.0f, 1.0f, 0.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(rotation.y), axis);

	axis = { 0.0f, 0.0f, 1.0f };
	mMatrix = glm::rotate(mMatrix, glm::radians(rotation.z), axis);

	mOrientation += rotation;
}

void Transform::Scale(const glm::vec3& scale)
{
	mMatrix = glm::scale(mMatrix, scale);
	mScale *= scale;
}

const glm::mat4& Transform::GetMatrix() const
{
	return mMatrix;
}
