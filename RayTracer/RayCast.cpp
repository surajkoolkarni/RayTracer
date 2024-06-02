#include "RayCast.h"
#include "Transform.h"

#include <fstream>
#include <random>


RayCaster::RayCaster(std::unique_ptr<Camera> camera, int width, int height) :
	m_camera(std::move(camera)),
	m_width(width),
	m_height(height)
{
}

glm::vec3 RayCaster::RayHitPixelToCamera(int x, int y)
{
	float aspect = (float)m_width / m_height;
	float Px = (2 * (x + 0.5) / m_width - 1) * tan(glm::radians(m_camera->fov / 2.)) * aspect;
	float Py = (1 - 2 * (y + 0.5) / m_height) * tan(glm::radians(m_camera->fov / 2.));
	return glm::vec3(Px, Py, -1);
}

Ray RayCaster::GenerateRay(int x, int y)
{
	glm::vec3 rayHitCamera = RayHitPixelToCamera(x, y);

	Ray ray;
	ray.origin = glm::vec3(m_camera->cameraToWorld * glm::vec4(0, 0, 0, 1));
	ray.dir = glm::normalize(glm::mat3(m_camera->cameraToWorld) * rayHitCamera);

	return ray;
}


glm::mat4 RayCaster::CameraToWorld()
{
	static bool isMatrixCalculated = false;

	//if (!isMatrixCalculated)
	//{
	//	isMatrixCalculated = true;
	//	m_camera->cameraToWorld = std::move(Transform::cameraToWorld(m_camera->eye, m_camera->center, m_camera->up));
	//}

	return m_camera->cameraToWorld;
}

// Trace a ray over scene (set of objects) and find nearest object
bool RayCaster::trace(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects,
	std::shared_ptr<IObject>& hitObject)
{
	float tNear = std::numeric_limits<float>::max();
	ray.t = std::numeric_limits<float>::max();

	for (size_t i = 0; i < objects.size(); ++i)
	{
		float t;
		if (objects[i]->intersect(ray.direction(), ray.origin, t) && t < tNear)
		{
			tNear = t;
			hitObject = objects[i];
		}
	}

	ray.t = tNear;

	return hitObject != nullptr;
}

inline glm::vec3 RayCaster::mix(const glm::vec3& a, const glm::vec3& b, const float& mixValue)
{
	return a * (1 - mixValue) + b * mixValue;
}

glm::vec3 RayCaster::CastRay(Ray& ray, const std::vector<std::shared_ptr<IObject>>& objects)
{
	glm::vec3 hitColor(0.);

	std::shared_ptr<IObject> hitObject = nullptr;

	if (trace(ray, objects, hitObject))
	{
		glm::vec3 nHit;
		glm::vec2 texCoord;

		glm::vec3 P = ray.origin + ray.t * ray.direction();

		hitObject->GetSurfaceData(P, nHit, texCoord);

		// Use the normal and texture coordinates to shade the hit point.
		// The normal is used to calculate a simple facing ratio, and the texture coordinate
		// to compute a basic checkerboard pattern.

		glm::vec3 dir = ray.direction();

		float scale = 4;
		float pattern = (fmodf(texCoord.x * scale, 1) > 0.5) ^ (fmodf(texCoord.y * scale, 1) > 0.5);
		hitColor = std::max(0.f, glm::dot(nHit, -dir)) * mix(hitObject->color, hitObject->color * 0.8f, pattern);
	}

	return hitColor;
}

float RayCaster::clamp(float min, float max, float value)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;

	return value;
}

void RayCaster::render(const std::vector<std::shared_ptr<IObject>>& objects)
{
	std::vector<glm::vec3> pixels(m_width * m_height);

	for (int j = 0; j < m_height; ++j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			Ray ray = GenerateRay(i, j);
			pixels[j * m_width + i] = CastRay(ray, objects);
		}
	}

	serialize(pixels);
}

void RayCaster::serialize(const std::vector<glm::vec3>& pixels)
{
	std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << m_width << " " << m_height << "\n255\n";
	for (uint32_t i = 0; i < m_height * m_width; ++i) {
		unsigned char r = (unsigned char)(255 * clamp(0, 1, pixels[i].x));
		unsigned char g = (unsigned char)(255 * clamp(0, 1, pixels[i].y));
		unsigned char b = (unsigned char)(255 * clamp(0, 1, pixels[i].z));
		ofs << r << g << b;
	}

	ofs.close();
}
