/**
 * @file Controller_Task.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Task of the controller module
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Task.hpp"

namespace banita
{
    class Controller_Task : public Task
    {
    public:

		/**
		 * @brief Construct a new Controller_Task object
		 * 
		 * @param _kernel 
		 */
		Controller_Task(Kernel * _kernel) : Task(_kernel, 2) {}

		/**
		 * @brief Construct a new Controller_Task object by default
		 * 
		 */
		Controller_Task() : Task(nullptr, 3) {}

	public:

		/**
		 * @brief initialize the controller's task attributes and members
		 * 
		 */
		void initialize() override;

		/**
		 * @brief update the controller's task attributes and members
		 * 
		 * @param _deltaTime 
		 */
		void execute(float _deltaTime) override;

		/**
		 * @brief terminate the controller task
		 * 
		 */
		void terminate() override;
    };
}