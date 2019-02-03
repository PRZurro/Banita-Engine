/**
 * @file Render_Module.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Module of the render type components (model, camera and light). Create components and store the task to update and initialize each component 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Module.hpp"
#include "Render_Task.hpp"

#include <list>

namespace banita
{
	class Render_Module : public Module
	{
	public:

		/**
		 * @brief Factory of the Render module
		 * 
		 */
		class Render_Factory : public Module::Factory
		{
		public:

			/**
			 * @brief Construct a new Render_Factory object 
			 * 
			 */
			Render_Factory();

		public:

			/**
			 * @brief Create a module object in the scene received
			 * 
			 * @param _scene 
			 * @return Module_sptr 
			 */
			Module_sptr create_module(Scene * _scene) override;
		};

	private:
		
		Render_Task task; 

	public:

		/**
		 * @brief Construct a new Render_Module object
		 * 
		 */
		Render_Module();

		/**
		 * @brief Construct a new Render_Module object
		 * 
		 * @param _owner 
		 */
		Render_Module(Scene * _owner);

		/**
		 * @brief Destroy the Render_Module object
		 * 
		 */
		~Render_Module() override
		{
		}

	public:

		// static Render_Factory * renderFactory; // Instancia un Render_Module_Factory

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

	public:

		/**
		 * @brief Create a component object to the entity received by parsing the xml node's attributes
		 * 
		 * @param _componentNode 
		 * @param _entity 
		 */
		void create_component(XML_Node * _componentNode, Entity * _entity) override;
	};

	//Render_Module::Render_Factory * Render_Module::renderFactory = new Render_Factory();
}