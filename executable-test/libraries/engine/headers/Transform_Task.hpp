/**
 * @file Transform_Task.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Process all events in which the components are affected or modified
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
	class Transform_Task : public Task
	{
	public:

		/**
		 * @brief Construct a new Transform_Task object and store the input kernel
		 * 
		 * @param _kernel 
		 */
		Transform_Task(Kernel * _kernel) : Task(_kernel, 1) {}

		/**
		 * @brief Construct a new Transform_Task object by default
		 * 
		 */
		Transform_Task() : Task(nullptr,1) {}

	public:

		/**
		 * @brief initialize all attributes and members of the transform components
		 * 
		 */
		void initialize() override;

		/**
		 * @brief update all attributes and members of the transform components
		 * 
		 * @param _deltaTime 
		 */
		void execute(float _deltaTime) override;

		/**
		 * @brief terminate this task
		 * 
		 */
		void terminate() override;
	};
}