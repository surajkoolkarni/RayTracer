#include "Mesh.h"
#include "Material.h"


Mesh::Mesh(uint32_t id, aiMesh* mesh, aiMaterial* material) :
	m_id(id)
{
	aiColor3D color;

	m_material = std::make_shared<Material>();

    material->Get(AI_MATKEY_COLOR_AMBIENT, m_material->ambient);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, m_material->diffuse);
    material->Get(AI_MATKEY_COLOR_SPECULAR, m_material->specular);
    material->Get(AI_MATKEY_SHININESS, m_material->shininess);

    loadTextures(material, aiTextureType_DIFFUSE, m_material->diffuseTexture);
    loadTextures(material, aiTextureType_SPECULAR, m_material->specularTexture);

    m_triangles = std::move(std::vector<std::shared_ptr<FacetTriangle>>(mesh->mNumFaces));

    for (size_t j = 0; j < mesh->mNumFaces; ++j)
    {
        aiVector3D* texture = mesh->mTextureCoords[0];

        m_triangles[j] = std::make_shared<FacetTriangle>(
            Vertex(mesh->mVertices[mesh->mFaces[j].mIndices[0]], mesh->mNormals[mesh->mFaces[j].mIndices[0]],
                texture ? aiVector2D(texture[mesh->mFaces[j].mIndices[0]].x, texture[mesh->mFaces[j].mIndices[0]].y) : aiVector2D()),
            Vertex(mesh->mVertices[mesh->mFaces[j].mIndices[1]], mesh->mNormals[mesh->mFaces[j].mIndices[1]],
                texture ? aiVector2D(texture[mesh->mFaces[j].mIndices[1]].x, texture[mesh->mFaces[j].mIndices[1]].y) : aiVector2D()),
            Vertex(mesh->mVertices[mesh->mFaces[j].mIndices[2]], mesh->mNormals[mesh->mFaces[j].mIndices[2]],
                texture ? aiVector2D(texture[mesh->mFaces[j].mIndices[2]].x, texture[mesh->mFaces[j].mIndices[2]].y) : aiVector2D()));
    }
}

void Mesh::loadTextures(aiMaterial* material, aiTextureType type, std::string& texture)
{
    uint32_t textureCount = material->GetTextureCount(type);

    for (size_t i = 0; i < textureCount; ++i)
    {
        aiString str;
        material->GetTexture(type, i, &str);

        texture = str.C_Str();

        break;
    }
}
