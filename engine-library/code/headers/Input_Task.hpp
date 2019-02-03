/**
 * @file Input_Task.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Task that process the peripherical state and translate it to engine lenguage
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Keyboard.hpp"
#include "Task.hpp"

#include <unordered_map>

namespace banita 
{
	class Kernel;
	class Message_Handler;

	class Input_Task : public Task
	{
	private:

		std::unordered_map<int, Keyboard::Key_Code> myKeyboardMapping;


	public:

		/**
		 * @brief Construct a new Input_Task object by the attributes received
		 * 
		 * @param _kernel 
		 * @param _priority 
		 * @param _isFinished 
		 */
		Input_Task(Kernel * _kernel, Size_t _priority = 50, bool _isFinished = false);

		/**
		 * @brief Destroy the Input_Task object
		 * 
		 */
		~Input_Task()
		{
		}

	public:

		/**
		 * @brief initialize the task attributes and members
		 * 
		 */
		void initialize() override;

		/**
		 * @brief update the task attributes and members
		 * 
		 * @param _deltaTime 
		 */

		/**
		 * @brief 
		 * 
		 * @param _deltaTime 
		 */
		void execute(float _deltaTime) override;

		/**
		 * @brief finalize this tasks
		 * 
		 */
		void terminate() override;

	public:

		/**
		 * @brief translates an Keyboard::Key_Code int (enum) to the action to which it should be translated
		 * 
		 * @param keycode 
		 * @return String 
		 */
		String translate_key_code_to_action(Keyboard::Key_Code keycode);
	};
}

