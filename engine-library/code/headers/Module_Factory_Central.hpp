/**
 * @file Module_Factory_Central.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Patch to the problem of auto-registration of static members in cpp files. Registers and stores the module factories 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Module.hpp"
#include "Render_Module.hpp"
#include "Controller_Module.hpp"
#include "Transform_Module.hpp"

#include <unordered_map>

namespace banita
{
	class Module_Factory_Central
	{
		using ModFactory_Map = std::unordered_map<Int32, Module::Factory*>;
		
	private:

		ModFactory_Map moduleFactories;

	private:

		/**
		 * @brief Construct a new Module_Factory_Central object
		 * 
		 */
		Module_Factory_Central() 
		{
			register_factory("transform", new Transform_Module::Transform_Factory());
			register_factory("render", new Render_Module::Render_Factory());
			register_factory("controller", new Controller_Module::Controller_Factory());
		}
		
		/**
		 * @brief Destroy the Module_Factory_Central object 
		 * 
		 */
		~Module_Factory_Central() {}

	public:

		static Module_Factory_Central * instance;

	public:

		/**
		 * @brief Singleton's implementation own member
		 * 
		 * @return Module_Factory_Central* 
		 */
		static Module_Factory_Central * get_instance()
		{
			if (instance)
				return instance;

			return instance = new Module_Factory_Central;
		}

		/**
		 * @brief register a new factory by name
		 * 
		 * @param _name 
		 * @param _factory 
		 */
		void register_factory(const String & _name, Module::Factory * _factory)
		{
			moduleFactories[FNV32(_name)] = _factory;
		}

		/**
		 * @brief Get the module factory object by name
		 * 
		 * @param _name 
		 * @return Module::Factory* 
		 */
		Module::Factory * get_module_factory(String & _name)
		{
			Int32 hashedName = FNV32(_name);

			return get_module_factory(hashedName);
		}

		/**
		 * @brief Get the module factory object by hashed name
		 * 
		 * @param _hashedName 
		 * @return Module::Factory* 
		 */
		Module::Factory * get_module_factory(Int32 _hashedName);
		
	};
}