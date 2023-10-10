#include "Renderer.h"

void Renderer::Draw(const VertexArray& vArray, const unsigned int& indicesCount, const Shader& shader) const
{
	shader.Bind();
	vArray.Bind();

	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}
