#include "RayCast.h"
#include "Sphere.h"

#include <random>
#include <memory>


int main(int argc, char** argv)
{
	// creating the scene (adding objects and lights)
	std::vector<std::shared_ptr<IObject>> objects;

	// generate a scene made of random spheres
	uint32_t numSpheres = 32;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	gen.seed(0);
	for (uint32_t i = 0; i < numSpheres; ++i) {
		glm::vec3 randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
		float randRadius = (0.5 + dis(gen) * 0.5);
		std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(randPos, randRadius, glm::vec3(dis(gen), dis(gen), dis(gen)));
		objects.push_back(std::move(sphere));
	}

	// setting up options
	int width = 640;
	int height = 480;
	float fov = 51.52;

	// finally, render
	std::unique_ptr<Camera> camera = std::make_unique<Camera>();
	camera->cameraToWorld = glm::mat4(glm::vec4(0.945519, 0, -0.325569, 0),
		glm::vec4(-0.179534, 0.834209, -0.521403, 0),
		glm::vec4(0.271593, 0.551447, 0.78876, 0),
		glm::vec4(4.208271, 8.374532, 17.932925, 1));
	camera->fov = fov;

	std::unique_ptr<IRayCaster> rayCaster = std::make_unique<RayCaster>(std::move(camera), width, height);
	rayCaster->render(objects);

	return 0;
}
