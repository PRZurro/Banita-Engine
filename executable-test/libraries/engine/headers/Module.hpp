/**
* @file Module.hpp
*
* @author Pablo Rodríguez Zurro
*
* @date 28/12/2018
*
* @class Class in charge of create components and process the information, attributes, members and logic that it has through his task 
*
* @brief
*/

#pragma once

#include "declarations.hpp"

#include <memory>
#include <unordered_map>

namespace banita
{
	class Task;
	class Scene;

	class Module
	{
	public:

		/**
		 * @brief Virtual pure factory of the module class
		 * 
		 */
		class Factory
		{
		public:
			virtual Module_sptr create_module(Scene * _scene) = 0;
		};

	private:

		//using ModFactory_Map = std::unordered_map<Int32, Factory*>;

	private:

		/*static ModFactory_Map moduleFactories;*/

	protected:

		Scene * owner; // Scene in which has been instanciated this module
		String name; 

	protected:

		/**
		 * @brief Construct a new Module object by defualt
		 * 
		 */
		Module();

		/**
		 * @brief Construct a new Module object storing the scene owner and it's received name
		 * 
		 * @param _owner 
		 * @param _name 
		 */
		Module(Scene * _owner, const String & _name = "undefined");

		/**
		 * @brief Destroy the Module object 
		 * 
		 */
		virtual ~Module() {}

	public:

		/////**
		////* @brief registers a new module factory to the list of factories by the input name
		////*
		////* @param _name
		////* @param _factory
		////*/
		////static void register_factory(const String & _name, Module::Factory * _factory)
		////{
		////	moduleFactories[FNV32(_name)] = _factory;
		////}

		////static Factory * get_module_factory(String & _name)
		////{
		////	Int32 hashedName = FNV32(_name);

		////	return get_module_factory(hashedName);
		////}

		////static Factory * get_module_factory(Int32 _hashedName) 
		////{
		////	Factory * factoryTemp = nullptr;

		////	if (moduleFactories.count(_hashedName) != 0) // If a pair with the given key is existing...
		////	{
		////		factoryTemp = moduleFactories[_hashedName];
		////	}
		////	return factoryTemp;
		////}

	public:

		/**
		 * @brief Create a component object to the entity received by processing the xml node received
		 * 
		 */
		virtual void create_component(XML_Node * _componentNode, Entity * _entity) = 0;

		
		/**
		* @brief Get the module's task
		*
		* @return Task*
		*/
		virtual Task * get_task() = 0;

		/**
		 * @brief Get the module's name
		 *
		 * @return const String&
		 */
		const String & get_name() const
		{
			return name;
		}

		/**
		 * @brief Get the scene object
		 * 
		 * @return Scene* 
		 */
		Scene * get_scene()
		{
			return owner;
		}
	};	

	//std::unordered_map<Int32, Module::Factory*> Module::moduleFactories = {};
}