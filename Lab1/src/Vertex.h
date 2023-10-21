#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;

	Vertex operator+(const Vertex& rhs)
	{
		return Vertex{this->pos + rhs.pos, rhs.normal};
	}
};