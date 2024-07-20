#include "Model.h"
#include "ModelRayCaster.h"

#include <chrono>
#include <iostream>

int main()
{
	std::unique_ptr<Model> model = std::make_unique<Model>("backpack.obj"); // space-shuttle-orbiter.obj
	//std::unique_ptr<Model> model = std::make_unique<Model>("space-shuttle-orbiter.obj");

	std::unique_ptr<Camera> camera = std::make_unique<Camera>();
	camera->eye = glm::vec3(1.16f, 1.44f, 4.41f);
	camera->center = glm::vec3(1.0f, 1.25f, 3.41f);
	camera->up = glm::vec3(0.0f, 1.0f, 0.f);
	camera->fov = 60.f; // 30.f

	//camera->eye = glm::vec3(-2086.1741055487196, 1488.3775094607265, 1234.451129921472);
	//camera->center = glm::vec3(9.264007500000021, 149.32280699999998, -82.22146599999996);
	//camera->up = glm::vec3(0.2501300083849314, 0.8490283395828082, -0.465387857051099);
	//camera->fov = 30.f;

	std::unique_ptr<ModelRayCaster> rayCaster = std::make_unique<ModelRayCaster>(std::move(model), std::move(camera), 1920, 1080);
	
	auto timeStart = std::chrono::system_clock::now();
	rayCaster->render();
	auto timeReq = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - timeStart);

	std::cout << "Time req to render: " << timeReq.count() << "sec" << std::endl;

	return 0;
}
