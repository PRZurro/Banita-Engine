/**
* @file Scene.hpp
*
* @author Pablo Rodr�guez Zurro
*
* @date 28/12/2018
*
* @class Scene.
*
* @brief
*/

#pragma once

#include "declarations.hpp"
#include "Entity.hpp"
#include "Module.hpp"
#include "Kernel.hpp"
#include "Message_Handler.hpp"
#include "Window.hpp"

#include <unordered_map>
#include <memory>
 
namespace banita
{ 
	class Scene
	{
		using Entities_Map = std::unordered_map<Int32, Entity_sptr>;
		using Modules_Map = std::unordered_map<Int32, Module_sptr>;
	
	private:

		Entities_Map entities;
		Modules_Map modules;

		Kernel * kernel;
		Window * window;
		Message_Handler * messageHandler;
		
	public:

		/**
		 * @brief Construct a new Scene object
		 * 
		 * @param _window 
		 * @param _scenePathXML 
		 */
		Scene(Window * _window, const String & _scenePathXML);
		
		/**
		 * @brief Destroy the Scene object
		 * 
		 */
		~Scene()
		{
			kernel->stop();
			modules.clear();

			delete kernel;
			delete messageHandler;
			delete window;
		}
		
	public:

		/**
		 * @brief 
		 * 
		 */
		void execute()
		{
			kernel->run();
		}

		/**
		 * @brief 
		 * 
		 */
		void pause()
		{
			kernel->pause();
		}

		/**
		 * @brief 
		 * 
		 */
		void stop()
		{
			kernel->stop();
		}

	public:

		/**
		 * @brief Get the kernel object
		 * 
		 * @return Kernel* 
		 */
		Kernel * get_kernel()
		{
			return kernel;
		}

		/**
		 * @brief Get the window object
		 * 
		 * @return Window* 
		 */
		Window * get_window()
		{
			return window;
		}

		/**
		 * @brief Get the message handler object
		 * 
		 * @return Message_Handler* 
		 */
		Message_Handler * get_message_handler()
		{
			return messageHandler;
		}

		/**
		 * @brief Get the entity object
		 * 
		 * @param _ID 
		 * @return Entity* 
		 */
		Entity * get_entity(Int32 _ID)
		{
			auto iterator = entities.find(_ID);

			if (iterator == entities.end())
				return nullptr;

			return iterator->second.get();
		}

		/**
		 * @brief Get the entity object
		 * 
		 * @param _ID 
		 * @return Entity* 
		 */
		Entity * get_entity(String & _ID)
		{
			return get_entity(FNV32(_ID));
		}

		/**
		 * @brief Get the module object
		 * 
		 * @param _name 
		 * @return Module* 
		 */
		Module * get_module(String & _name)
		{
			auto iterator = modules.find(FNV32(_name));

			if (iterator == modules.end())
				return nullptr;
		
			return iterator->second.get();
		}

	private:

		/**
		 * @brief load the scene by the file path received
		 * 
		 * @param _filePath 
		 * @return true 
		 * @return false 
		 */
		bool load_scene(const String & _filePath);

		/**
		 * @brief load the scene's entities by parsing the entities node
		 * 
		 * @param _entities 
		 * @return true 
		 * @return false 
		 */
		bool load_entities(XML_Node * _entities);

		/**
		 * @brief load the entity's components by parsing the components node
		 * 
		 * @param _componentRoot 
		 * @param _entity 
		 * @return true 
		 * @return false 
		 */
		bool load_components(XML_Node * _componentRoot, Entity & _entity);

		/**
		 * @brief load a module by name if is not existing yet
		 * 
		 * @param _moduleName 
		 * @return true 
		 * @return false 
		 */
		bool load_module(String & _moduleName);
	};
}