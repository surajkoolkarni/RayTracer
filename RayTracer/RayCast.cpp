#include "RayCast.h"
#include "Transform.h"

#include <random>


RayCaster::RayCaster(std::unique_ptr<Camera> camera, int width, int height) :
	IRayCaster(std::move(camera), width, height)
{
}

inline glm::vec3 RayCaster::mix(const glm::vec3& a, const glm::vec3& b, const float& mixValue)
{
	return a * (1 - mixValue) + b * mixValue;
}
