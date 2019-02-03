#include "declarations.hpp"
#include "Render_Module.hpp"
#include "Entity.hpp"
#include "Scene.hpp"
#include "Component_Generator.hpp"
#include "Camera_Component.hpp"
#include "Model_Component.hpp"
#include "Light_Component.hpp"
#include "Render_Task.hpp"

#include <rapidxml.hpp>

using namespace rapidxml;

namespace banita
{
	//Render_Module::Render_Factory * Render_Module::renderFactory = new Render_Factory; // Auto-registration at compilation time

	Render_Module::Render_Factory::Render_Factory()
	{
		//Module::register_factory("render", this);
	}

    Module_sptr Render_Module::Render_Factory::create_module(Scene * _scene)
    {
        return Module_sptr(new Render_Module(_scene));
    }

	Render_Module::Render_Module(): Module(nullptr, "render") , task(nullptr)
	{}

	Render_Module::Render_Module(Scene * _owner) : Module(_owner, "render"), task(owner->get_kernel())
	{}

	void Render_Module::create_component(XML_Node * _componentNode, Entity * _entity)
	{
		String componentType = "", componentName = ""; 

		// <component module = "render" name = "x" type = "camera"|"light"|"model"(obj) ></component>
		//		<property1></property1>

		if (_componentNode->type() == node_element)
		{
			XML_Attr * attributeXML = _componentNode->first_attribute("type");

			if (String(attributeXML->name()) == "type")
			{
				componentType = attributeXML->value(); // It is recolected the component type with the node attribute
			}

			attributeXML = _componentNode->first_attribute("name");

			if (String(attributeXML->name()) == "name")
			{
				componentName = attributeXML->value(); // It is recolected the component name with the node attribute
			}
		}

		fnComponentGenerator componentGenerator = nullptr;

		componentGenerator = Component_Generator::get_instance()->get_component_generator("render",componentType); // we get the component generator (pointer to function that returns a Component_sptr)
		//
		if (!componentGenerator) // if the component generator is different to nullptr...
			return;

		Component_sptr tempComponent = componentGenerator(_entity);  //Create a component with the given component generator (pointer to function)
		tempComponent->set_name(componentName); // the component is created with the entity pointer parameter constructor (without type and name parameters) so is necessary to set the custom name

		XML_Node * propertyNode = _componentNode->first_node(); // get the first child of the nodes hierarchy

		for (propertyNode; propertyNode; propertyNode = propertyNode->next_sibling())
		{
			// Iterate through the sibling nodes, that in this case are component properties
			if (propertyNode->type() == node_element)
			{
				if (!tempComponent->parse_property(String(propertyNode->name()), String(propertyNode->value())))// let the component handle the property values
				{
					return;
				}
			}
			else break;
		}
			
		//glt::Render_Node * rendererTemp = task.get_renderer();


	/*	if (rendererTemp)
		{*/
			if (componentType == "camera")
			{
				std::shared_ptr<Camera_Component> cameraComponent = std::static_pointer_cast<Camera_Component> (tempComponent);

				//camera->set_renderer(task.get_render_node());
				task.renderer.add(tempComponent->get_name(), cameraComponent->get_camera());
				//renderNode->set_active_camera(cameraComponent->get_name());

				SDL_Log("Adding a camera to the scene...");
			}
			else if (componentType == "model")
			{
				std::shared_ptr<Model_Component> modelComponent = std::static_pointer_cast<Model_Component> (tempComponent);

				//model->set_renderer(task.get_render_node());
				task.renderer.add(tempComponent->get_name(), modelComponent->get_model());

				SDL_Log("Adding a 3D model to the scene...");
			}
			else if (componentType == "light")
			{
				std::shared_ptr<Light_Component> lightComponent = std::static_pointer_cast<Light_Component> (tempComponent);
				//light->set_renderer(task.get_render_node());
				task.renderer.add(tempComponent->get_name(), lightComponent->get_light());

				SDL_Log("Adding a light to the scene...");
			}
		//}
		
		_entity->add_component(componentName, tempComponent); // add the component to the entity's component map
		task.add_component(_entity->get_component(componentName));
	}
}