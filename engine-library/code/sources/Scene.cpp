#include "Scene.hpp"
#include "Kernel.hpp"
#include "Module_Factory_Central.hpp"
#include "Module.hpp"
#include "Input_Task.hpp"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <rapidxml.hpp>

using namespace rapidxml;
using namespace std;

namespace banita
{
	Scene::Scene(Window * _window, const String & _scenePathXML) : kernel(new Kernel(this)), window(_window)/*, messageHandler(message_handler::get_instance())*/
	{
		messageHandler = new Message_Handler();

		load_scene(_scenePathXML);

		auto iterator = modules.begin(); 
		auto end = modules.end();
		for (iterator; iterator != end; ++iterator)
		{
			kernel->add_task(*iterator->second->get_task());
		}
	}

	bool Scene::load_scene(const String & _filePath)
	{
		bool loaded = false;

		xml_document<> doc;
		xml_node<> * rootNode;

		// Read the xml file into a vector
		ifstream theFile(_filePath);
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');

		// parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		 //find our root node
		rootNode = doc.first_node("scene");
		
		if(rootNode)
			load_entities(rootNode->first_node("entities"));

		return loaded;
	}

	bool Scene::load_entities(XML_Node * _entities)
	{
		bool loaded = true;

		xml_node<> * entityNode = _entities->first_node("entity");

		for (entityNode; entityNode; entityNode = entityNode->next_sibling())
		{
			if (entityNode->type() == node_element)
			{
				// Iterate over each entity node
				String name = "";
				if (String(entityNode->name()) == "entity")
				{
					if (String(entityNode->first_attribute()->name()) == "id")
					{
						name = entityNode->first_attribute()->value();
					}

					Entity_sptr entityTemp(new Entity(name, this));
					entities[FNV32(name)] = entityTemp;
					load_components(entityNode->first_node("components"), *entityTemp);
				}
			}
			else
				loaded = false;
		}
		return loaded;
	}

	bool Scene::load_components(XML_Node * _componentRoot, Entity & _entity)
	{
		bool loaded = false;
		//The pointer must point to the first node children of the components node
		_componentRoot = _componentRoot->first_node("component");
		
		for (_componentRoot; _componentRoot; _componentRoot = _componentRoot->next_sibling())
		{
			if(_componentRoot->type() == node_element)
			{
				// Iterate over each component node
				if(String(_componentRoot->name()) == "component")
				{
					XML_Attr * moduleAttributeTemp = _componentRoot->first_attribute("module");

					if (moduleAttributeTemp)
					{
						String moduleType = moduleAttributeTemp->name();

						if (String(moduleAttributeTemp->name()) == "module") // If the has a module type..
						{
							moduleType = moduleAttributeTemp->value();
							load_module(moduleType);

							Module * module = get_module(moduleType); // Get the corresponding instantiated module with the type of the component

							if (module)
							{
								// If the module  is existing, create the component in it's specialized method, sending the node. 
								module->create_component(_componentRoot, &_entity); 
							}
						}
					}
				}
			}	
		}

		return loaded;
	}
	bool Scene::load_module(String & _moduleName)
	{
		bool loaded = false;

		if (_moduleName != "")
		{
			if (!get_module(_moduleName))
			{
				Module::Factory * factory = Module_Factory_Central::get_instance()->get_module_factory(_moduleName);
				

				if (factory)
				{
					modules[FNV32(_moduleName)] = factory->create_module(this);
					loaded = true;
				}
			}
		}

		return loaded;
	}
}