/**
* @file Component.hpp
*
* @author Pablo Rodríguez Zurro
*
* @date 28/12/2018
*
* @class Component
*
* @brief Component virtual class 
*/

#pragma once

#include "declarations.hpp"
#include "Node.hpp"

namespace banita
{
	class Component
	{
	protected:

		Entity * owner;
		String type; // stores the module type
		String name;

	public: 

		/**
		 * @brief Construct a new Component object by default
		 * 
		 */
		Component();

		/**
		 * @brief Construct a new Component object, storing and processing the children's input objects
		 * 
		 */
		Component(Entity * _owner, String _type = "undefined", String _name = "undefined");

		virtual ~Component() {}

	public:

		/**
		 * @brief Get the entity object
		 * 
		 * @return Entity& 
		 */
		Entity & get_entity() const
		{
			return *owner;
		}

		/**
		 * @brief Get the type object
		 * 
		 * @return const String& 
		 */
		const String & get_type() const 
		{
			return type;
		}

		/**
		 * @brief Get the name object
		 * 
		 * @return const String& 
		 */
		const String & get_name() const
		{
			return name;
		}


	public:

		/**
		 * @brief Set the name object
		 * 
		 * @param _newName 
		 */
		void set_name(String & _newName)
		{
			name = _newName;
		}

	public:

		/**
		 * @brief initialize the attributes and logic of this component
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool initialize() = 0;

		/**
		 * @brief update this component
		 * 
		 * @param _deltaTime provided by the kernel
		 * @return true 
		 * @return false 
		 */
		virtual bool update(float _deltaTime) = 0;

		/**
		 * @brief parse the xml property node in each children 
		 * 
		 * @param _name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		virtual bool parse_property(const String & _name, const String & value) = 0;
	};
}