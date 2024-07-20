#pragma once

#include "IRayCaster.h"
#include "Model.h"


class RAY_TRACER_API ModelRayCaster final
{
public:
	ModelRayCaster(std::unique_ptr<Model> model, std::unique_ptr<Camera> camera, int width, int height);

	~ModelRayCaster();

	void Render();

	void Serialize(const std::string& fileName);

private:
	bool trace(Ray& ray, const std::vector<std::shared_ptr<FacetTriangle>>& objects, std::shared_ptr<FacetTriangle>& hitTriangle);

	Ray GenerateRay(int x, int y);

	glm::vec3 RayHitPixelToCamera(int x, int y);

	bool CastRay(Ray& ray, std::shared_ptr<Mesh> mesh, glm::vec3& P, std::shared_ptr<FacetTriangle>& hitTriangle);


	glm::mat4 CameraToWorld() const;

	aiColor3D CalculateColor(const std::shared_ptr<FacetTriangle> triangle, const Image& image);

	int GetTextureIndex(const aiVector2D& texCoords, const Image& image);

	aiColor3D GetColorFromImageData(int index, const Image& image);

	bool intersectsAABB(const std::shared_ptr<Mesh> mesh, const Ray& ray, const float& t);

	aiColor3D ComputeShading(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<FacetTriangle> hitTriangle, const glm::vec3& P);

private:
	std::unique_ptr<Camera> m_camera{};

	std::unique_ptr<Model> m_model{};

	int m_height{}, m_width{};

	unsigned char* m_pixels{};
};
