#include "Sphere.h"
#include "Utils.h"

#include <utility>

#include <math.h>

using namespace glm;

Sphere::Sphere(const glm::vec3& center, float radius, const glm::vec3& color_) :
	m_center(center), m_radius(radius)
{
	color = color_;
}

bool Sphere::intersect(const glm::vec3& dir, const glm::vec3& origin, float& t) const
{
	float a = glm::dot(dir, dir);
	float b = 2 * glm::dot(origin - m_center, dir);
	float c = glm::dot(origin - m_center, origin - m_center) - m_radius * m_radius;

	if (b * b - 4 * a * c < 0)
		return false;

	float t1, t0;

	SolveQuadraticEquation(a, b, c, t0, t1);
	
	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1; // If t0 is negative, let's use t1 instead
		if (t0 < 0) return false; // Both t0 and t1 are negative
	}

	t = t0;
	
	return true;
}

void Sphere::GetSurfaceData(const glm::vec3& pHit, glm::vec3& nHit, glm::vec2& texCoord)
{
	nHit = pHit - m_center;
	nHit = glm::normalize(nHit);

#define M_PI 3.14159265358979323846
	// In this particular case, the normal is simular to a point on a unit sphere
	// centred around the origin. We can thus use the normal coordinates to compute
	// the spherical coordinates of Phit.
	// atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
	// acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
	texCoord.x = (1 + atan2(nHit.z, nHit.x) / M_PI) * 0.5;
	texCoord.y = acosf(nHit.y) / M_PI;
}
