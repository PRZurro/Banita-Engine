#include "BanitaEngine.hpp"
#include "Scene.hpp"
#include "declarations.hpp"
#include "Window.hpp"
#include "Input_Task.hpp"
#include "Message.hpp"
#include "Transform_Component.hpp"

namespace banita
{
	BanitaEngine::BanitaEngine()
	{
	}
	void BanitaEngine::run(std::string scenePath, int windowWidth, int windowHeight, std::string windowName, bool fullscreen )
	{
		/*SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);*/

		Window window(windowName, windowWidth, windowHeight, fullscreen);

		window.enable_vsync();
		Scene scene1(&window, scenePath);

		Kernel * kernel = scene1.get_kernel();
		Input_Task inputTask(kernel);
		kernel->add_task(inputTask); //The task to check the input is created

		scene1.execute();
	}
}