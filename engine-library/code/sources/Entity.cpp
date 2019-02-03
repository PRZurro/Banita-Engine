
#include "Entity.hpp"

banita::Entity::Entity(Scene * _scene) : name("Undefined")
{
}

banita::Entity::Entity(String & _name, Scene * _scene) : name(_name), scene(_scene) {}

bool banita::Entity::initialize()
{
	bool result = true;

	for (auto component : components)
	{
		if (!component.second->initialize())
		{
			result = false;
		}
	}

	return result;
}

bool banita::Entity::add_component(const String & _name, Component_sptr _component)
{
	std::size_t found = _name.find("transform");
	if (found != std::string::npos)
	{
		if (_component.get())
		{
			transform = std::dynamic_pointer_cast<Transform_Component>(_component);
		}
		return true;
	}

	bool added = false;

	Int32 hashedName = FNV32(_name);

	if (components.count(hashedName) == 0)
	{
		components[hashedName] = _component;

		added = true;
	}
	else
	{
		return true;
	}
	return added;
}
