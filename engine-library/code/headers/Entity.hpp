/**
 * @file Entity.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Entity class. An entity is an object that belongs to an engine's scene and has components 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Component.hpp"
#include "Transform_Module.hpp"

#include <unordered_map>
#include <memory>


namespace banita 
{
	class Scene;

	class Entity
	{
		using Components = std::unordered_map< Size_t, Component_sptr>;
		using Tr_Comp_sptr = std::shared_ptr< Transform_Component>;

	private:

		String name; // It's necessary for my architecture to store each one of the entities's name because there is no fast way to decipher the INT32 Hash to String
		Components components;
		Scene * scene; 

		Tr_Comp_sptr transform; // Shared pointer to transform component that stores an OpenGL Toolkit's node. 

	public:

		/**
		 * @brief Construct a new Entity object and store the scene pointer received
		 * 
		 * @param _scene 
		 */
		Entity(Scene * _scene);

		/**
		 * @brief Construct a new Entity object and store the scene pointer and name received
		 * 
		 * @param _name 
		 * @param _scene 
		 */
		Entity(String & _name, Scene * _scene);

		/**
		 * @brief Destroy the Entity object
		 * 
		 */
		~Entity() 
		{
			//Destroy components
		}

	public:

		/**
		 * @brief initialize the attributes and members of this entity
		 * 
		 * @return true 
		 * @return false 
		 */
		bool initialize();

	public:

		/**
		 * @brief add a component to this entity
		 * 
		 * @param _type 
		 * @param _component 
		 * @return true 
		 * @return false 
		 */
		bool add_component(const String & _type, Component_sptr _component);
		
	public:

		/**
		 * @brief return the name object
		 * 
		 * @return String& 
		 */
		String & get_name()
		{
			return name;
		}

		/**
		 * @brief return the transform object
		 * 
		 * @return Transform_Component& 
		 */
		Transform_Component & get_transform()
		{
			return *transform;
		}

		/**
		 * @brief return the component object
		 * 
		 * @param _ID 
		 * @return Component* 
		 */
		Component * get_component(Int32 _ID)
		{
			auto iterator = components.find(_ID);

			if (iterator == components.end())
				return nullptr;

			return iterator->second.get();
		}

		/**
		 * @brief return the component object
		 * 
		 * @param _type 
		 * @return Component* 
		 */
		Component * get_component(const String & _type)
		{
			return get_component(FNV32(_type));
		}
		
		/**
		 * @brief Get the scene object
		 * 
		 * @return Scene* 
		 */
		Scene * get_scene()
		{
			return scene;
		}
	};
}