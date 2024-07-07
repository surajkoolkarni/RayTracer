#pragma once

#include "IObject.h"

#include "Triangle.h"

#include "Vertex.h"

class PRIMITIVES_API FacetTriangle final : public IObject
{
public:
	FacetTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	bool intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const override;

	void GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& textCoord) override;

public:
	Vertex p1;
	Vertex p2;
	Vertex p3;

	static int s_i;

public:
	mutable BaryCenter baryCenter;
};
