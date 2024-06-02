#include "Utils.h"

#include <glm/glm.hpp>

void SolveQuadraticEquation(float a, float b, float c, float& t1, float& t2)
{
	t1 = (-b + glm::sqrt(b * b - 4 * a * c)) / (2 * a);
	t2 = (-b - glm::sqrt(b * b - 4 * a * c)) / (2 * a);
}
