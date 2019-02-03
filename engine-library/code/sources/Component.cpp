#include "Component.hpp"
#include "declarations.hpp"

namespace banita 
{
	Component::Component() : owner(nullptr), type("undefined"), name("undefined") {}
	Component::Component(Entity *  _owner , String _type, String _name ) :  owner(_owner) , type(_name) , name() {}
}