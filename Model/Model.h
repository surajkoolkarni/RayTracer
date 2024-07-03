#pragma once

#include "ModelApi.h"

#include "Mesh.h"
#include "FacetTriangle.h"
#include "Material.h"

#include <assimp/scene.h>

#include <map>
#include <memory>
#include <string>
#include <vector>


class MODEL_API Model
{
public:
    Model(const std::string& path);

    Model(const Model&) = delete;
    Model(Model&&) = default;

    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = default;

private:
    void loadModel(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);

    void loadTextureMaps(aiMaterial* material, aiTextureType type, std::map<std::string, unsigned char*>& textureMap);

public:
    std::map<std::string, unsigned char*> m_diffuseMaps;
    std::map<std::string, unsigned char*> m_specularMaps;

private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
};
