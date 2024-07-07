#include "Model.h"
#include "ModelRayCaster.h"


int main()
{
	std::unique_ptr<Model> model = std::make_unique<Model>("backpack.obj");

	std::unique_ptr<Camera> camera = std::make_unique<Camera>();
	camera->eye = glm::vec3(1.16f, 1.44f, 4.41f);
	camera->center = glm::vec3(1.0f, 1.25f, 3.41f);
	camera->up = glm::vec3 (0.0f, 1.0f, 0.f);
	camera->fov = 60.f;

	std::unique_ptr<ModelRayCaster> rayCaster = std::make_unique<ModelRayCaster>(std::move(model), std::move(camera), 640, 480);
	rayCaster->render();

	return 0;
}
