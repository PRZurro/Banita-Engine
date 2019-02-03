/**
 * @file Transform_Module.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Module of the transform components. 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"

#include "Module.hpp"
#include "Transform_Component.hpp"
#include "Transform_Task.hpp"

#include <memory>

namespace banita
{
	class Scene; 

	class Transform_Module : public Module
	{
	public:

		/**
		 * @brief Factory of the transform module
		 * 
		*/
		class Transform_Factory : public Factory
		{
		public:

			/**
			 * @brief Construct a new Transform_Factory object
			 * 
			 */
			Transform_Factory();// Invoca a Module::register_module(id, this)

		public:

			/**
			 * @brief Create a transform module in the received scene
			 * 
			 * @param _scene 
			 * @return Module_sptr 
			 */
			Module_sptr create_module(Scene * _scene) override;
		};

	public:

		/**
		 * @brief Construct a new Transform_Module object by default
		 * 
		 */
		Transform_Module();

		/**
		 * @brief Construct a new Transform_Module object saving the received entity
		 * 
		 * @param _owner 
		 */
		Transform_Module(Scene * _owner);

		/**
		 * @brief Destroy the Transform_Module object
		 * 
		 */
		~Transform_Module(){}

	private:

			Transform_Task task;

	public:

		//static Transform_Factory * transformFactory; // instance to a transform module factory

	public:

		/**
		 * @brief Create a component object in the entity received by parsing the attributes and values of the xml node
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

	//Transform_Module::Transform_Factory * Transform_Module::transformFactory = new Transform_Factory();
}