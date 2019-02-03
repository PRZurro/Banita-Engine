#include "Camera_Component.hpp"
#include "Component_Generator.hpp"
#include "Entity.hpp"
#include "Transform_Component.hpp"
#include "Camera.hpp"

namespace banita
{
	
	//fnComponentGenerator Camera_Component::generatorInstance = Component_Generator::get_instance()->register_component_generator("render","camera", Camera_Component::generator);

	Camera_Component::Camera_Component(Entity * _owner, float _fov, float _aspectRatio, float _nearPlaneD, float _farPlaneD) 
		: Component(_owner, "camera"), camera(new glt::Camera(_fov, _nearPlaneD, _farPlaneD, _aspectRatio))
	{
	}
	bool Camera_Component::initialize()
	{
		camera->translate(owner->get_transform().get_position());
		camera->set_transformation(owner->get_transform().get_transformation());
		/*camera->set_parent(&owner->get_transform().get_node());*/
		return true;
	}
	bool Camera_Component::update(float _deltaTime)
	{
		camera->set_transformation(owner->get_transform().get_transformation());
		
		camera->set_visible(owner->get_transform().get_visibility()); // This would work?
		return true;
	}
	bool Camera_Component::parse_property(const String & _name, const String & value)
	{
		return true;
	}
}

