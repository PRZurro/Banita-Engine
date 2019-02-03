
#include "Component_Generator.hpp"

namespace banita
{

	Component_Generator * Component_Generator::instance;

	fnComponentGenerator Component_Generator::get_component_generator(String _module, String _type)
	{
		auto iterator = mapOfGeneratorMaps.find(_module);

		if (iterator != mapOfGeneratorMaps.end())
		{
			auto iterator = mapOfGeneratorMaps[_module].find(_type);

			if (iterator != mapOfGeneratorMaps[_module].end())
				return mapOfGeneratorMaps[_module][_type];
		}

		return nullptr;
	}
}