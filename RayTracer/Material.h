#pragma once

#include <assimp/types.h>

#include <string>
#include <vector>
#include <map>

struct Material
{
	Material() = default;

	aiColor3D ambient;
	aiColor3D diffuse;
	aiColor3D specular;

	float shininess;

	std::vector<std::string> diffuseTextures;
	std::vector<std::string> specularTextures;

	//unsigned char* normalMap;
	//unsigned char* heightMap;
};
