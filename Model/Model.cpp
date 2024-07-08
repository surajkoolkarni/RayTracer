#include "Model.h"

#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <glm/vec3.hpp>

#include <iostream>


Model::Model(const std::string& path)
{
    loadModel(path);
}

Model::~Model()
{
    for (auto i : m_diffuseMaps)
        stbi_image_free(i.second.data);

    for (auto i : m_specularMaps)
        stbi_image_free(i.second.data);
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (size_t i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(std::make_shared<Mesh>(node->mMeshes[i], mesh, scene->mMaterials[mesh->mMaterialIndex]));

        loadTextureMaps(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_DIFFUSE, m_diffuseMaps);
        loadTextureMaps(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_SPECULAR, m_specularMaps);
    }

    for (size_t i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::loadTextureMaps(aiMaterial* material, aiTextureType type, std::map<std::string, Image>& textureMap)
{
    uint32_t textureCount = material->GetTextureCount(type);

    for (size_t i = 0; i < textureCount; ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);

        // Avoid duplication of textures
        if (textureMap.find(str.C_Str()) == textureMap.end())
        {
            int width, height, channels;

            stbi_info(str.C_Str(), &width, &height, &channels);

            std::cout << "Width:" << width << " Height:" << height << " Channels:" << channels << std::endl;

            unsigned char* data = stbi_load(str.C_Str(), &width, &height, &channels, 3);

            if (stbi_failure_reason() && !data && !strcmp((const char*)data, ""))
                std::cout << stbi_failure_reason() << std::endl;

            textureMap[str.C_Str()] = Image{ data, width, height, channels };
        }
    }
}
