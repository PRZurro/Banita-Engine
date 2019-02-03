#include "Controller_Module.hpp"
#include "declarations.hpp"
#include "Controller_Module.hpp"
#include "Component_Generator.hpp"
#include "Scene.hpp"
#include "Controller_Task.hpp"


using namespace rapidxml;

namespace banita
{
	//Controller_Module::Controller_Factory * Controller_Module::controllerFactory = new Controller_Factory(); // Auto-registration at compilation time

	Controller_Module::Controller_Factory::Controller_Factory()
	{
       // Module::register_factory("controller", this);
	}
	Module_sptr Controller_Module::Controller_Factory::create_module(Scene * _scene)
	{
		return Module_sptr(new Controller_Module(_scene));
	}
	Controller_Module::Controller_Module() 
		: task(owner->get_kernel()) {}

	Controller_Module::Controller_Module(Scene * _owner) : Module(_owner, "controller"), task(owner->get_kernel()) {}

	void Controller_Module::create_component(XML_Node * _componentNode, Entity * _entity)
	{
		if (_componentNode->type() == node_element)
		{
			if (String(_componentNode->name()) == "component")
			{
				XML_Attr * attr = _componentNode->first_attribute("type");

				if (String(attr->value()) == "playercontroller")
				{
					String name = "playercontroller";

					fnControllerComponentGenerator fn = Component_Generator::get_instance()->get_controller(name);
					Component_sptr componentTemp = fn(_entity, owner->get_message_handler());

					XML_Attr * attrName = _componentNode->first_attribute("name");

					if (String(attrName->name()) == "name")
					{
						String name = String(attrName->value());
						componentTemp->set_name(name);
					}		
					_entity->add_component(name, componentTemp);
					task.add_component(_entity->get_component(name));
				}
			}
			
		}
	}
}

