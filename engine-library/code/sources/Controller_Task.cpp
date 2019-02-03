#include "Controller_Task.hpp"
#include "Component.hpp"

namespace banita
{
	void Controller_Task::initialize()
	{
		for (auto * component : components)
		{
			component->initialize();
		}
	}

	void Controller_Task::execute(float _deltaTime)
	{
		for (auto & component : components)
		{
			component->update(_deltaTime);
		}
	}

	void Controller_Task::terminate()
	{

		isFinished = true;
	}

}
