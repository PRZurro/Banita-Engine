/**
 * @file Render_Task.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Task of the render module
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Task.hpp"
#include "Render_Node.hpp"
#include "Kernel.hpp"
#include "Scene.hpp"

namespace banita
{
	class Render_Task : public Task
	{
		using Render_Node = glt::Render_Node;
		//using Render_Node_str = std::shared_ptr<glt::Render_Node>;

	public:

		Render_Node renderer;

	public:

		/**
		 * @brief Construct a new Render_Task object
		 * 
		 * @param _kernel 
		 */
		Render_Task(Kernel * _kernel);

		/**
		 * @brief Construct a new Render_Task object
		 * 
		 */
		Render_Task();

	public:

		/**
		 * @brief initialize the members and attributes of this task
		 * 
		 */
		void initialize() override;

		/**
		 * @brief update the members and attributes of this task
		 * 
		 * @param _deltaTime 
		 */
		void execute(float _deltaTime) override;

		/**
		 * @brief finalize this task
		 * 
		 */
		void terminate() override;


		/**
		 * @brief renderize the scene by the window and renderer node members
		 * 
		 */
		void renderize();
	};
}