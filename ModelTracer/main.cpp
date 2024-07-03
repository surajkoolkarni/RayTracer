#include "Model.h"

int main()
{
	std::unique_ptr<Model> model = std::make_unique<Model>("backpack.obj");

	return 0;
}
