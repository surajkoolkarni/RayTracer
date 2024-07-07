#pragma once

#include "RayTracerExport.h"

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

class RAY_TRACER_API IRayCaster
{
public:
	IRayCaster(std::unique_ptr<Camera> camera, int width, int height);

	virtual void render(const std::vector<std::shared_ptr<IObject>>& objects);

	virtual bool trace(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects, std::shared_ptr<IObject>& hitObject);

private:
	glm::vec3 CastRay(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects);

	glm::vec3 RayHitPixelToCamera(int x, int y);

	Ray GenerateRay(int x, int y);


	glm::mat4 CameraToWorld();

	float clamp(float min, float max, float value);

	void serialize(const std::vector<glm::vec3>& pixels);

private:
	std::unique_ptr<Camera> m_camera;

	int m_height{}, m_width{};
};

