#pragma once

#include "IObject.h"

#include <glm/glm.hpp>

class PRIMITIVES_API Sphere final : public IObject
{
public:
	Sphere(const glm::vec3& center, float radius, const glm::vec3& color);

	~Sphere() = default;

	bool intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const override;

	void GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& textCoord) override;

private:
	glm::vec3 m_center;

	float m_radius;
};
