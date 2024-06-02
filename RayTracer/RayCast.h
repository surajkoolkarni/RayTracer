#pragma once

#include "Ray.h"
#include "IObject.h"

#include <vector>
#include <memory>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

struct Intersection
{
	bool intersected;

	glm::vec3 point;
	glm::vec3 normal;
};

struct Camera
{
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	float fov;

	glm::mat4 cameraToWorld;
};

class RAY_TRACER_API RayCaster
{
public:
	RayCaster(std::unique_ptr<Camera> camera, int width, int height);
	
	void render(const std::vector<std::shared_ptr<IObject>>& objects);

private:
	glm::vec3 CastRay(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects);

	glm::vec3 RayHitPixelToCamera(int x, int y);

	Ray GenerateRay(int x, int y);

	bool trace(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects, std::shared_ptr<IObject>& hitObject);

	glm::mat4 CameraToWorld();

	glm::vec3 mix(const glm::vec3& a, const glm::vec3& b, const float& mixValue);

	float clamp(float min, float max, float value);

	void serialize(const std::vector<glm::vec3>& pixels);

private:
	std::unique_ptr<Camera> m_camera;

	int m_height{}, m_width{};
};
