

#include "Transform_Component.hpp"
#include "Component_Generator.hpp"
#include "declarations.hpp"

#include <vector>

namespace banita
{

	//fnComponentGenerator Transform_Component::generatorInstance = Component_Generator::get_instance()->register_component_generator("transform", "transform", Transform_Component::generator);

	Transform_Component::Transform_Component(Entity * _owner): Component(_owner, "transform"), visible(true) // we create an empty node(transform)
	{
	}

	bool Transform_Component::initialize()
	{
		return true;
	}
	bool Transform_Component::update(float _deltaTime)
	{
		move(movementList); // if it is added a movement, it will not be processed until the next tick/frame

		return true;
	}
	bool Transform_Component::parse_property(const String & _name, const String & _value)
	{
		std::vector<String> values = String_Utilities::string_splitter(_value, ',');

		if (values.size())
		{
			if (_name == "position")
			{
				float x = std::stof(values[0]), y = std::stof(values[1]), z = std::stof(values[2]);
				set_position(x, y, z);
			}
			else if (_name == "rotation")
			{
				float x = std::stof(values[0]), y = std::stof(values[1]), z = std::stof(values[2]);
				rotate(x, y, z);

			}
			else if (_name == "scale")
			{
				scale(std::stof(_value));
			}
		}
		else
			return false;
		
		return true;
	}
}
