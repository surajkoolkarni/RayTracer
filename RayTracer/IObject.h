#pragma once

#include "Ray.h"
#include "RayTracerExport.h"


class RAY_TRACER_API IObject
{
public:
	virtual ~IObject() 
	{
	}

	virtual bool intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const = 0;

	virtual void GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& textCoord) = 0;

	glm::vec3 color;
};
