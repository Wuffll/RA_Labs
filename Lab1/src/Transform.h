#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:

	Transform();
	Transform(const glm::mat4& matrix);

	~Transform();

	void SetPosition(const glm::vec3& pos);
	void SetOrientation(const glm::vec3& orientation);

	void ResetScale();

	void Translation(const glm::vec3& translation);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);

	const glm::mat4& GetMatrix() const;

private:

	glm::mat4 mMatrix{ 1.0f };
	glm::vec3 mPosition{ 0.0f };
	glm::vec3 mOrientation{ 0.0f };
	glm::vec3 mScale{ 1.0f };

};