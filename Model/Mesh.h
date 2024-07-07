#pragma once

#include "Vertex.h"
#include "FacetTriangle.h"
#include "Material.h"

#include <assimp/mesh.h>
#include <assimp/material.h>

#include <memory>
#include <vector>
#include <cstdint>


class Mesh
{
public:
	Mesh(uint32_t id, aiMesh* mesh, aiMaterial* material);

private:
	void loadTextures(aiMaterial* material, aiTextureType type, std::string& textures);

public:
	uint32_t m_id;
	std::vector<std::shared_ptr<FacetTriangle>> m_triangles;
	std::shared_ptr<Material> m_material;
};
