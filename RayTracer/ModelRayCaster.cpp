#include "ModelRayCaster.h"
#include "Transform.h"

#include "stb_image_write.h"

#include <fstream>
#include <iostream>


ModelRayCaster::ModelRayCaster(std::unique_ptr<Model> model, std::unique_ptr<Camera> camera, int width, int height) :
	m_model(std::move(model)),
	m_camera(std::move(camera)),
	m_width(width),
	m_height(height)
{
	m_camera->cameraToWorld = std::move(Transform::cameraToWorld(m_camera->eye, m_camera->center, m_camera->up));
}

bool ModelRayCaster::trace(Ray& ray, const std::vector<std::shared_ptr<FacetTriangle>>& triangles, std::shared_ptr<FacetTriangle>& hitObject)
{
	float tNear = std::numeric_limits<float>::max();
	ray.t = std::numeric_limits<float>::max();

	for (size_t i = 0; i < triangles.size(); ++i)
	{
		float t;
		if (triangles[i]->intersect(ray.direction(), ray.origin, t) && t < tNear)
		{
			tNear = t;
			hitObject = triangles[i];
		}
	}

	ray.t = tNear;

	return hitObject != nullptr;
}

void ModelRayCaster::render()
{
	m_pixels = new unsigned char[m_width * m_height * 3];

	std::fill(m_pixels, m_pixels + m_width * m_height * 3, 0.f);

	for (int j = 0; j < m_height; ++j)
	{
		std::cout << "j: " << j << std::endl;
		for (int i = 0; i < m_width; ++i)
		{
			Ray ray = GenerateRay(i, j);
			for (auto mesh : m_model->m_meshes)
			{
				aiColor3D color;
				if (CastRay(ray, mesh, color))
				{
					m_pixels[(j * m_width + i) * 3 + 0] = (unsigned char)(255 * glm::clamp(color.r, 0.f, 1.f));
					m_pixels[(j * m_width + i) * 3 + 1] = (unsigned char)(255 * glm::clamp(color.g, 0.f, 1.f));
					m_pixels[(j * m_width + i) * 3 + 2] = (unsigned char)(255 * glm::clamp(color.b, 0.f, 1.f));
				}
			}
		}
	}

	serialize();

	delete[] m_pixels;
}

bool ModelRayCaster::CastRay(Ray& ray, std::shared_ptr<Mesh> mesh, aiColor3D& color)
{
	glm::vec3 lightPos(0.7f, 0.2f, 2.0f);
	aiColor3D ambientLight(0.2, 0.2, 0.2);
	aiColor3D diffuseLight(0.5, 0.5, 0.5);
	aiColor3D specularLight(1.0f, 1.0f, 1.0f);

	std::shared_ptr<FacetTriangle> hitTriangle = nullptr;

	if (!trace(ray, mesh->m_triangles, hitTriangle))
		return false;

	glm::vec3 P = ray.origin + ray.t * ray.direction();

	aiVector3D normal = hitTriangle->baryCenter.u * hitTriangle->p1.Normal + hitTriangle->baryCenter.v * hitTriangle->p2.Normal + hitTriangle->baryCenter.w * hitTriangle->p3.Normal;
	// Use the normal and texture coordinates to shade the hit point.
	// The normal is used to calculate a simple facing ratio, and the texture coordinate
	// to compute a basic checkerboard pattern.

	std::shared_ptr<Material> material = mesh->m_material;

	Image diffuseImage = m_model->m_diffuseMaps[material->diffuseTexture];
	Image specularImage = m_model->m_specularMaps[material->specularTexture];

	aiColor3D diffuse = material->diffuse;
	aiColor3D specular = material->specular;

	if (!material->diffuseTexture.empty())
		diffuse = CalculateColor(hitTriangle, diffuseImage);
		
	if (!material->specularTexture.empty())
		specular = CalculateColor(hitTriangle, specularImage);

	glm::vec3 reflectionDir = glm::reflect(-glm::normalize(lightPos - P), glm::vec3(normal.x, normal.y, normal.z));

	float spec = pow(glm::max(glm::dot(glm::normalize(m_camera->eye - P), reflectionDir), 0.f), material->shininess);

	color = ambientLight + diffuse * diffuseLight + specular * spec * specularLight;

	return true;
}

Ray ModelRayCaster::GenerateRay(int x, int y)
{
	glm::vec3 rayHitCamera = RayHitPixelToCamera(x, y);

	Ray ray;
	ray.origin = glm::vec3(CameraToWorld() * glm::vec4(0, 0, 0, 1));
	ray.dir = glm::normalize(glm::mat3(CameraToWorld()) * rayHitCamera);

	return ray;
}

glm::vec3 ModelRayCaster::RayHitPixelToCamera(int x, int y)
{
	float aspect = (float)m_width / m_height;
	float Px = (2 * (x + 0.5) / m_width - 1) * tan(glm::radians(m_camera->fov / 2.)) * aspect;
	float Py = (1 - 2 * (y + 0.5) / m_height) * tan(glm::radians(m_camera->fov / 2.));
	return glm::vec3(Px, Py, -1);
}

void ModelRayCaster::serialize()
{
	stbi_write_png("out.png", m_width, m_height, 3, m_pixels, m_width * 3);
}

glm::mat4 ModelRayCaster::CameraToWorld() const	
{
	return m_camera->cameraToWorld;
}

int ModelRayCaster::GetIndex(const aiVector2D& texCoords, const Image& image)
{
	int x = static_cast<int>(texCoords.x * (image.width - 1));
	int y = static_cast<int>((1.f - texCoords.y) * (image.height - 1));
	int index = (y * image.width + x) * image.channels;

	return index;
}

aiColor3D ModelRayCaster::GetColor(int index, const Image& image)
{
	if (!image.data || !strcmp((const char*)image.data, ""))
		return aiColor3D(1., 1., 1.);

	float R = image.data[index] / 255.0f;
	float G = image.data[index + 1] / 255.0f;
	float B = image.data[index + 2] / 255.0f;

	return aiColor3D(R, G, B);
}

aiColor3D ModelRayCaster::CalculateColor(const std::shared_ptr<FacetTriangle> triangle, const Image& image)
{
	int index1 = GetIndex(triangle->p1.TexCoords, image);
	int index2 = GetIndex(triangle->p2.TexCoords, image);
	int index3 = GetIndex(triangle->p3.TexCoords, image);

	return GetColor(index1, image) * triangle->baryCenter.u + GetColor(index2, image) * triangle->baryCenter.v + GetColor(index3, image) * triangle->baryCenter.w;
}
