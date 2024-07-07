#pragma once

#include "ModelApi.h"

#include "Mesh.h"
#include "FacetTriangle.h"
#include "Material.h"
#include "Image.h"

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

    void render();

private:
    void loadModel(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);

    void loadTextureMaps(aiMaterial* material, aiTextureType type, std::map<std::string, Image>& textureMap);

public:
    std::map<std::string, Image> m_diffuseMaps;
    std::map<std::string, Image> m_specularMaps;

    std::vector<std::shared_ptr<Mesh>> m_meshes;
};
