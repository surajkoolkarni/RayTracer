#pragma once

#include "PrimitivesApi.h"

#include <assimp/vector3.h>
#include <assimp/vector2.h>

struct PRIMITIVES_API Vertex
{
    Vertex(const aiVector3D& pos, const aiVector3D& normal, const aiVector2D& texcoords);

    aiVector3D Position;
    aiVector3D Normal;
    aiVector2D TexCoords;

    //aiVector3D Tangent;
    //aiVector3D Bitangent;

    //int BoneIDs[4];

    //float Weights[4];
};
