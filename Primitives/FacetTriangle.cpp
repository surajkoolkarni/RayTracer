#include "FacetTriangle.h"

#include <iostream>

FacetTriangle::FacetTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) :
	p1(v1), p2(v2), p3(v3)
{
}

glm::vec3 ToVec3(const aiVector3D& aiVec)
{
    return glm::vec3(aiVec.x, aiVec.y, aiVec.z);
}

bool FacetTriangle::intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const
{
    // calculate plane intersection first
    glm::vec3 normal = glm::cross(ToVec3(p2.Position) - ToVec3(p1.Position), ToVec3(p3.Position) - ToVec3(p1.Position));

    float dirDotNormal = glm::dot(dir, normal);
    if (fabs(dirDotNormal) < 1e-6)
        return false;

    t = -(glm::dot(origin, normal) - glm::dot(ToVec3(p1.Position), normal)) / dirDotNormal;

    // ray is behind triangle
    // check if ray direction and normal are parallel
    // also enable back face culling
    if (t < 0)
        return false;

    glm::vec3 intersection = origin + t * dir;

    float NDotN = glm::dot(normal, normal);

    // check if the point is inside or not
    baryCenter.u = glm::dot(glm::cross(ToVec3(p2.Position) - ToVec3(p1.Position), intersection - ToVec3(p1.Position)), normal) / NDotN;

    if (baryCenter.u < 0 || baryCenter.u > 1)
        return false;

    baryCenter.v = glm::dot(glm::cross(ToVec3(p3.Position) - ToVec3(p2.Position), intersection - ToVec3(p2.Position)), normal) / NDotN;

    if (baryCenter.v < 0 || baryCenter.v > 1)
        return false;

    baryCenter.w = (1.f - baryCenter.u - baryCenter.v);

    return true;
}

void FacetTriangle::GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& textCoord)
{
}

int FacetTriangle::s_i = 0;