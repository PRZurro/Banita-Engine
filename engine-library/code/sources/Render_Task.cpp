
#include "Render_Task.hpp"
#include "Component.hpp"
#include "SDL_log.h"


#include "Model.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Cube.hpp"
#include "Drawable.hpp"
#include "Scene.hpp"
#include "Window.hpp"

using namespace std;
using namespace glt;

namespace banita
{
	Render_Task::Render_Task(Kernel * _kernel) : Task(_kernel, 2)/*, renderer(_rNode)*/
	{
	}

	Render_Task::Render_Task() : Task(nullptr, 2) {}

	void Render_Task::initialize()
	{
		for (Component * component : components)
		{
			component->initialize();
		}
	}

	void Render_Task::execute(float _deltaTime)
	{
		for (Component * component : components )
		{
			component->update(_deltaTime);
		}

		renderize();
	}

	void Render_Task::terminate()
	{
		isFinished = true;
	}

	void Render_Task::renderize()
	{
		Window * window = kernel->get_scene()->get_window();

		GLsizei width = GLsizei(window->get_width());
		GLsizei height = GLsizei(window->get_height());

		renderer.get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);

		window->clear();

		renderer.render();

		window->swap_buffers();
	}
}