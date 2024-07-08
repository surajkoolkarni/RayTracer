#pragma once

#include "IRayCaster.h"
#include "Model.h"


class RAY_TRACER_API ModelRayCaster final
{
public:
	ModelRayCaster(std::unique_ptr<Model> model, std::unique_ptr<Camera> camera, int width, int height);

	void render();

private:
	bool trace(Ray& ray, const std::vector<std::shared_ptr<FacetTriangle>>& objects, std::shared_ptr<FacetTriangle>& hitObject);

	Ray GenerateRay(int x, int y);

	glm::vec3 RayHitPixelToCamera(int x, int y);

	bool CastRay(Ray& ray, std::shared_ptr<Mesh> mesh, aiColor3D& color);

	void serialize();

	glm::mat4 CameraToWorld() const;

	aiColor3D CalculateColor(const std::shared_ptr<FacetTriangle> triangle, const Image& image);

	int GetIndex(const aiVector2D& texCoords, const Image& image);

	aiColor3D GetColor(int index, const Image& image);

private:
	std::unique_ptr<Camera> m_camera{};

	std::unique_ptr<Model> m_model{};

	int m_height{}, m_width{};

	unsigned char* m_pixels{};
};
