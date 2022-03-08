#pragma once
#include "glm\glm.hpp"

using namespace std;
namespace Rendering
{

	struct VertexFormat
	{
		glm::vec3 position; //a vertex attribute
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 texture;
		VertexFormat(const glm::vec3 &position, const glm::vec4 &color, glm::vec3 &normal)
		{
			this->position = position;
			this->color = color;
			this->normal = normal;
		}

		VertexFormat(const glm::vec3 &position, const glm::vec2 &text, glm::vec3 &normal)
		{
			this->position = position;
			this->texture = text;
			this->normal = normal;
		}

		VertexFormat(const glm::vec3 &position, const glm::vec2 &text)
		{
			this->position = position;
			this->texture = text;
		}
		VertexFormat(){}
	};

}