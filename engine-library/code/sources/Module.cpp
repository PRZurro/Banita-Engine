
#include "Module.hpp"

namespace banita
{

	//std::unordered_map<Int32, Module::Factory*> Module::moduleFactories = {};

	Module::Module() : owner(nullptr), name("undefined") {}
	Module::Module(Scene * _owner, const String & _name) : owner(_owner), name(_name) {}
}
