#pragma once

#include "Transform.h"

class Drawable
{
public:

	virtual void Draw() const = 0;
	virtual Transform& GetTransform() = 0;
};