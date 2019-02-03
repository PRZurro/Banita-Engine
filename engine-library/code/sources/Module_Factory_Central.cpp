
#include "Module_Factory_Central.hpp"


namespace banita
{
	Module_Factory_Central * Module_Factory_Central::instance;

	Module::Factory * Module_Factory_Central::get_module_factory(Int32 _hashedName)
	{
		Module::Factory * factoryTemp = nullptr;

		if (moduleFactories.count(_hashedName) != 0) // If a pair with the given key is existing...
		{
			factoryTemp = moduleFactories[_hashedName];
		}
		return factoryTemp;
	}
}