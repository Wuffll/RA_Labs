#pragma once

#include <glm/glm.hpp>

class Drawable
{
public:

	virtual void Draw() const = 0;
	virtual const glm::mat4& GetTransform() const
	{
		return glm::mat4(1.0f);
	}

};