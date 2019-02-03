#include "Light_Component.hpp"
#include "Entity.hpp"
#include "Transform_Component.hpp"
#include "Component_Generator.hpp"
#include "SDL_log.h"


namespace banita
{
	//fnComponentGenerator Light_Component::generatorInstance = Component_Generator::get_instance()->register_component_generator("render", "light", Light_Component::generator);

    Light_Component::Light_Component(Entity * _entity) : Component(_entity, "light"), light(new glt::Light())
	{
	}
	bool Light_Component::initialize()
	{
		light->set_transformation(owner->get_transform().get_transformation());
		//light->set_parent(&owner->get_transform().get_node());
		return true;
	}
	bool Light_Component::update(float _deltaTime)
	{
		light->set_transformation(owner->get_transform().get_transformation());
		light->set_visible(owner->get_transform().get_visibility());
		return true;
	}
	bool Light_Component::parse_property(const String & _name, const String & _value)
	{	
		std::vector<String> values = String_Utilities::string_splitter(_value.c_str(), ',');

		if (_name == "color") 
		{
			Vector3f colorVector(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]));
			light->set_color(colorVector);
		}
		else if (_name == "intensity")
		{
			light->set_intensity(std::stof(values[0]));
		}
	
		return true;
	}
	void Light_Component::set_color(float _r, float _g, float _b)
	{
		light->set_color(Vector3f(_r, _g, _b));
	}
	void Light_Component::set_color(Vector3f _color)
	{
		light->set_color(_color);
	}
	void Light_Component::set_intensity(float _intensity)
	{
		light->set_intensity(_intensity);
	}
}