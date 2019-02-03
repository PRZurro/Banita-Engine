#include "Input_Task.hpp"
#include "Message_Handler.hpp"
#include "Message.hpp"
#include "Kernel.hpp"
#include "Scene.hpp"

#include <vector>
	
namespace banita
{
	Input_Task::Input_Task(Kernel * _kernel, Size_t _priority, bool _isFinished) 
		: Task(_kernel, _priority, _isFinished)
	{
		Input_Task::myKeyboardMapping =
		{
			{Keyboard::KEY_W, Keyboard::KEY_W},
			{Keyboard::KEY_ARROW_UP, Keyboard::KEY_ARROW_UP},
			{Keyboard::KEY_S, Keyboard::KEY_S},
			{Keyboard::KEY_ARROW_DOWN, Keyboard::KEY_ARROW_DOWN},
			{Keyboard::KEY_A, Keyboard::KEY_A},
			{Keyboard::KEY_ARROW_LEFT, Keyboard::KEY_ARROW_LEFT},
			{Keyboard::KEY_D, Keyboard::KEY_D},
			{Keyboard::KEY_ARROW_RIGHT, Keyboard::KEY_ARROW_RIGHT}
		};

	}

	void Input_Task::initialize()
	{
	}

	void Input_Task::execute(float _deltaTime)
	{
		
		Window::Event event;

		Window * window = kernel->get_scene()->get_window();
		

		while (window->poll(event))
		{
			switch (event.type)
			{
				case Window::Event::CLOSE:
				{
					kernel->stop();
					break;
				}

				case Window::Event::KEY_PRESSED:
				{
					if (event.data.keyboard.key_code == Keyboard::KEY_ESCAPE)
					{
						kernel->stop();
					}

					//auto iterator = std::find(myKeyboardMapping.begin(), myKeyboardMapping.end(), event.data.keyboard.key_code); //Bug

					if (myKeyboardMapping.count(event.data.keyboard.key_code) != 0)
					{
						String messageID = KEY_PRESSED_ID;
						String direction = translate_key_code_to_action(myKeyboardMapping[event.data.keyboard.key_code]);
					
						Message message = Message(messageID); // a message with an identifier is created

						SDL_Log(direction.c_str());
						Var property (direction);

						message.add_property(direction, property); // add the key pressed to the properties of the message

						kernel->get_scene()->get_message_handler()->multicast(message); //Let the listeners handle the created message
					}

					break;
				}
			}
		}

	}

	void Input_Task::terminate()
	{
		isFinished = true;
	}

	String Input_Task::translate_key_code_to_action(Keyboard::Key_Code _keycode)
	{
		switch (_keycode)
		{
			case Keyboard::KEY_W:
			case Keyboard::KEY_ARROW_UP:

				return "up";

			case Keyboard::KEY_S:
			case Keyboard::KEY_ARROW_DOWN:

				return "down";

			case Keyboard::KEY_A:
			case Keyboard::KEY_ARROW_LEFT:

				return "left";

			case Keyboard::KEY_D:
			case Keyboard::KEY_ARROW_RIGHT:

				return "right";
		}

		return "unknown";
	}
}




