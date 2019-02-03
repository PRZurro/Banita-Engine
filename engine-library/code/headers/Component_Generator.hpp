/**
 * @file Component_Generator.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Generator of components, store and create components 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Transform_Component.hpp"
#include "Camera_Component.hpp"
#include "Light_Component.hpp"
#include "Model_Component.hpp"
#include "Player_Controller.hpp"

#include <unordered_map>
#include <list>

namespace banita
{
	class Component_Generator
	{
		using generatorsMap = std::unordered_map<String, fnComponentGenerator >;

	private:

		static Component_Generator * instance; // instance of this component generator

		//Here will be stored the generators of diferent module
		std::unordered_map<String, generatorsMap> mapOfGeneratorMaps;

		std::unordered_map<String, fnControllerComponentGenerator> controllerGenerators; // Associated with Controller_Module

	public:

		/**
		 * @brief Construct a new Component_Generator object. Currently doing a unintended step in order to register new component. 
		 * Each component should auto-register invoking this instance
		 * 
		 */
		Component_Generator()
		{
			register_component_generator("transform", "transform", Transform_Component::generator);
			register_component_generator("render", "camera", Camera_Component::generator);
			register_component_generator("render", "light", Light_Component::generator);
			register_component_generator("render", "model", Model_Component::generator);
			register_controller("playercontroller", Player_Controller::generator);
		}

		/**
		 * @brief Destroy the Component_Generator object and it's maps
		 * 
		 */
		~Component_Generator()
		{
			auto iterator = mapOfGeneratorMaps.begin(), end = mapOfGeneratorMaps.end();

			for (iterator; iterator!= end; ++iterator)
				iterator->second.clear();

			mapOfGeneratorMaps.clear();
			controllerGenerators.clear();
		}

	public:

		/**
		 * @brief register a new component generator function pointer 
		 * 
		 * @param _module 
		 * @param _type 
		 * @param _generator 
		 * @return the component generator function pointer that receives 
		 */
		fnComponentGenerator register_component_generator(String _module, String _type,  fnComponentGenerator _generator)
		{
			return mapOfGeneratorMaps[_module][_type] = _generator;
		}

		/**
		 * @brief 
		 * 
		 * @param _type 
		 * @param _generator 
		 * @return the controller function pointer that receives  
		 */
		fnControllerComponentGenerator register_controller(String _type, fnControllerComponentGenerator _generator)
		{
			return controllerGenerators[_type] = _generator;
		}
		

	public:

		/**
		 * @brief Get the instance object
		 * 
		 * @return Component_Generator* 
		 */
		static Component_Generator * get_instance()
		{
			if (instance)
				return instance;

			return instance = new Component_Generator;
		}

		/**
		 * @brief Get the controller generator function pointer
		 * 
		 * @param _type 
		 * @return fnControllerComponentGenerator 
		 */
		fnControllerComponentGenerator get_controller(String _type)
		{
			auto iterator = controllerGenerators.find(_type);

			if (iterator == controllerGenerators.end())
				return nullptr;

			return iterator->second;
		}
		
		/**
		 * @brief Get the component generator function pointer
		 * 
		 * @param _module 
		 * @param _type 
		 * @return fnComponentGenerator 
		 */
		fnComponentGenerator get_component_generator(String _module, String _type);
		
		/**
		 * @brief Get the controller generator function pointer
		 * 
		 * @param _type 
		 * @return fnControllerComponentGenerator 
		 */
		fnControllerComponentGenerator get_controller_generator(String _type)
		{
			return controllerGenerators[_type];
		}
	};
}
