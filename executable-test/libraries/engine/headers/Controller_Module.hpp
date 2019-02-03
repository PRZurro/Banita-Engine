/**
 * @file Controller_Module.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Module of the controllers. Create components and store the task to update and initialize each component 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "Module.hpp"
#include "Controller_Task.hpp"

namespace banita
{
	class Controller_Module : public Module
	{
	public:

		/**
		 * @brief Factory of the controller module
		 * 
		 */
		class Controller_Factory : public Factory
		{
		public:

			/**
			 * @brief Construct a new Controller_Factory object and auto-register to the module instance 
			 * 
			 */
			Controller_Factory(); // invoke Module::register_module(id, this)

		public:

			/**
			 * @brief Create a module object in the received scene
			 * 
			 * @param _scene 
			 * @return Module_sptr 
			 */
			Module_sptr create_module(Scene * _scene) override;
		};

	private:

		Controller_Task task;

	public:

		/**
		 * @brief Construct a new Controller_Module object by default
		 * 
		 */
		Controller_Module();

		/**
		 * @brief Construct a new Controller_Module object in the received scene
		 * 
		 * @param _owner 
		 */
		Controller_Module(Scene * _owner);

		~Controller_Module(){}



	public:

		//static Controller_Factory * controllerFactory; // instance to a controller module factory, deprecated by library limitations

	public:

		/**
		 * @brief Create a component object by processing the received xml node to the input entity
		 * 
		 * @param _componentNode 
		 * @param _entity 
		 */
		void create_component(XML_Node * _componentNode, Entity * _entity) override;
		
	public:

		/**
		 * @brief Get the task object
		 * 
		 * @return Task* 
		 */
		Task * get_task() override
		{
			return &task;
		}
	};

	//Controller_Module::Controller_Factory * Controller_Module::controllerFactory = new Controller_Factory();
}