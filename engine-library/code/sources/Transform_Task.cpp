#include "Transform_Task.hpp"
#include "Component.hpp"
#include "SDL_log.h"

namespace banita
{
	void Transform_Task::initialize()
	{
		for (auto & component : components)
		{
			String name = component->get_name();
			SDL_Log(name.c_str());
			component->initialize();
		}
	}

	void Transform_Task::execute(float _deltaTime)
	{	
		for (auto & component : components)
		{
			component->update(_deltaTime);
		}
	}

	void Transform_Task::terminate()
	{
		isFinished = true;
	}
}
