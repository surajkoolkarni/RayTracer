#include "Triangle.h"

Triangle::Triangle(const glm::vec3& p1_, const glm::vec3& p2_, const glm::vec3& p3_) :
    p1(p1_), p2(p2_), p3(p3_)
{
    normal = glm::normalize(glm::cross(p1 - p2, p1 - p3));
}

// barycentric coordinates
bool Triangle::intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const
{
    // calculate plane intersection first
    
    // check if ray direction and normal are parallel
    // also enable back face culling

    if (glm::dot(dir, normal) < 0)
        return false;

    t = glm::dot((p1 - origin), normal) / glm::dot(dir, normal);

    // ray is behind triangle
    if (t < 0)
        return false;

    glm::vec3 intersection = origin + t * dir;

    // check if the point is inside or not
    if (baryCentric.u = glm::dot(glm::normalize(glm::cross(p2 - p1, intersection - p1)), normal) < 0)
        return false;

    if (baryCentric.v = glm::dot(glm::normalize(glm::cross(p3 - p2, intersection - p2)), normal) < 0)
        return false;

    if (baryCentric.w = glm::dot(glm::normalize(glm::cross(p1 - p3, intersection - p3)), normal) < 0)
        return false;

    return true;
}

void Triangle::GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& texCoord)
{
    nHit = normal;


}

