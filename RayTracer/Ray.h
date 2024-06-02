#pragma once

#include <glm/glm.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 dir;

	float t;

	glm::vec3 direction() const
	{
		return glm::normalize(dir);
	}
};
