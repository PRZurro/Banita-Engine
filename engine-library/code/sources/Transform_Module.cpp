#include "declarations.hpp"
#include "Transform_Module.hpp"
#include "Transform_Component.hpp"
#include "Entity.hpp"
#include "Scene.hpp"
#include "Component_Generator.hpp"

#include <rapidxml.hpp>

using namespace rapidxml;

namespace banita 
{
    //Transform_Module::Transform_Factory * Transform_Module::transformFactory = new Transform_Factory(); // Auto-registration at compilation time

	Transform_Module::Transform_Factory::Transform_Factory()
	{
		/*Module::register_factory("transform", this);*/
	}

    Module_sptr Transform_Module::Transform_Factory::create_module(Scene * _scene)
    {
        return Module_sptr(new Transform_Module(_scene));
    }

	Transform_Module::Transform_Module() 
		: Module(nullptr, "transform"), task(nullptr) 
	{}

	Transform_Module::Transform_Module(Scene * _owner)
		: Module(_owner, "transform"), task(owner->get_kernel()) 
	{}

	void Transform_Module::create_component(XML_Node * _componentNode, Entity * _entity)
	{
		fnComponentGenerator fn = Component_Generator::get_instance()->get_component_generator("transform", "transform");

		if (!fn)
			return;

		Component_sptr transformComponentTemp(fn(_entity));

		XML_Node * propertyNode = _componentNode->first_node(); // get the first child of the nodes hierarchy

		for (propertyNode; propertyNode; propertyNode = propertyNode->next_sibling())
		{
			// Iterate through the sibling nodes, that in this case are component properties
			if (propertyNode->type() == node_element)
			{
				transformComponentTemp->parse_property(String(propertyNode->name()), String(propertyNode->value())); // let the component handle the property values
			}
			else break;
		}
		_entity->add_component("transform", transformComponentTemp); // add the component to the entity's component map
		task.add_component(&_entity->get_transform());
		
	}
}