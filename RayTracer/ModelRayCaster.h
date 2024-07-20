#pragma once

#include "IRayCaster.h"
#include "Model.h"


class RAY_TRACER_API ModelRayCaster final
{
public:
	enum Direction
	{
		X, Y, Z
	};

public:
	ModelRayCaster(std::unique_ptr<Model> model, std::unique_ptr<Camera> camera, int width, int height);

	void render();

private:
	bool trace(Ray& ray, const std::vector<std::shared_ptr<FacetTriangle>>& objects, std::shared_ptr<FacetTriangle>& hitObject);

	Ray GenerateRay(int x, int y);

	glm::vec3 RayHitPixelToCamera(int x, int y);

	bool CastRay(Ray& ray, std::shared_ptr<Mesh> mesh, glm::vec3& P, std::shared_ptr<FacetTriangle>& hitTriangle);

	void serialize();

	glm::mat4 CameraToWorld() const;

	aiColor3D CalculateColor(const std::shared_ptr<FacetTriangle> triangle, const Image& image);

	int GetIndex(const aiVector2D& texCoords, const Image& image);

	aiColor3D GetColor(int index, const Image& image);

	int IntersectingAABBId(const Ray& ray, Direction dir);

	bool intersectsAABB(const std::shared_ptr<Mesh> mesh, const Ray& ray, const float& t);

	int CalculateId(const Ray& ray, Direction dir);

	aiColor3D ComputeShading(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<FacetTriangle> hitTriangle, const glm::vec3& P);

private:
	std::unique_ptr<Camera> m_camera{};

	std::unique_ptr<Model> m_model{};

	int m_height{}, m_width{};

	unsigned char* m_pixels{};
};
