#pragma once

#include "RayTracerExport.h"

#include "IRayCaster.h"

class RAY_TRACER_API RayCaster final : public IRayCaster
{
public:
	RayCaster(std::unique_ptr<Camera> camera, int width, int height);
	
private:
	glm::vec3 mix(const glm::vec3& a, const glm::vec3& b, const float& mixValue);
};
