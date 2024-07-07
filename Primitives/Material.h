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

	std::string diffuseTexture;
	std::string specularTexture;

	//unsigned char* normalMap;
	//unsigned char* heightMap;
};
