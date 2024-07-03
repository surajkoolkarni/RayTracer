#include "FacetTriangle.h"

FacetTriangle::FacetTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) :
	p1(v1), p2(v2), p3(v3)
{
}

bool FacetTriangle::intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const
{
	return false;
}

void FacetTriangle::GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& textCoord)
{
}
