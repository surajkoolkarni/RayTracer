#include "Triangle.h"

#include <cmath>

Triangle::Triangle(const glm::vec3& p1_, const glm::vec3& p2_, const glm::vec3& p3_) :
    p1(p1_), p2(p2_), p3(p3_)
{
    normal = glm::cross(p2 - p1, p3 - p1);
}

Triangle::Triangle(const glm::vec3& p1_, const glm::vec3& p2_, const glm::vec3& p3_, const glm::vec3& n_) :
    p1(p1_), p2(p2_), p3(p3_), normal(n_)
{
}

// baryCenter coordinates
bool Triangle::intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const
{
    // calculate plane intersection first
    float dirDotNormal = glm::dot(dir, normal);
    if (fabs(dirDotNormal) < 1e-6)
        return false;

    t = - (glm::dot(origin, normal) - glm::dot(p1, normal)) / dirDotNormal;

    // ray is behind triangle
    // check if ray direction and normal are parallel
    // also enable back face culling
    if (t < 0)
        return false;

    glm::vec3 intersection = origin + t * dir;

    float NDotN = glm::dot(normal, normal);

    // check if the point is inside or not
    baryCenter.u = glm::dot(glm::cross(p2 - p1, intersection - p1), normal) / NDotN;

    if (baryCenter.u < 0 || baryCenter.u > 1)
        return false;

    baryCenter.v = glm::dot(glm::cross(p3 - p2, intersection - p2), normal) / NDotN;

    if (baryCenter.v < 0 || baryCenter.v > 1)
        return false;

    baryCenter.w = glm::dot(glm::cross(p1 - p3, intersection - p3), normal) / NDotN;

    if (baryCenter.w < 0 || baryCenter.w > 1)
        return false;

    return true;
}

void Triangle::GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& texCoord)
{
}

