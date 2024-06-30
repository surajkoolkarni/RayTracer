#pragma once

#include "IObject.h"

struct BaryCentric
{
	float u, v, w;
};

class RAY_TRACER_API Triangle final : public IObject
{
public:
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

	bool intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const override;

	void GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& texCoord) override;

private:
	glm::vec3 p1, p2, p3;
	glm::vec3 normal;

public:
	mutable BaryCentric baryCentric;
};
