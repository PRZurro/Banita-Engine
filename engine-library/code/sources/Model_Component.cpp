#include "Model_Component.hpp"
#include "declarations.hpp"
#include "Render_Module.hpp"
#include "Component_Generator.hpp"
#include "Entity.hpp"
#include "SDL_log.h"
#include "SDL_test_log.h"

namespace banita
{
	//fnComponentGenerator Model_Component::generatorInstance = Component_Generator::get_instance()->register_component_generator("render", "model", Model_Component::generator);

	Model_Component::Model_Component(Entity * _owner) : Component( _owner , "model")
	{
	}
	Model_Component::Model_Component(Entity * _owner, const String & _modelPath) : Component( _owner , "Model")
	{
	}
	bool Model_Component::initialize()
	{
		model->set_transformation(owner->get_transform().get_transformation());
		//model->set_parent(&owner->get_transform().get_node());

		return true;
	}
	bool Model_Component::update(float _deltaTime)
	{
		model->set_transformation(owner->get_transform().get_transformation());
		model->set_visible(owner->get_transform().get_visibility());

		return true;
	}
	bool Model_Component::parse_property(const String & _name, const String & value)
	{
		//relative path to the library resources folder
		String relativePath = "../../assets/obj/";
		//relative path to the application resources folder
		String relativePathBuild = "assets/obj/";
		
		String valueInstance = value;

		if (valueInstance.size() == 0)
		{
			return false;
		}


		relativePath += valueInstance;
		relativePathBuild = valueInstance;

		model.reset(new glt::Model_Obj(relativePath));

		//try again in the executable assets folder
		if (!model->is_ok())
		{
			String error = model->get_error();
			SDL_Log(error.c_str());

			glt::Model_Obj * modelTemp2();
			model.reset(new glt::Model_Obj(relativePathBuild));
			
			// model loading failed 
			if (!model->is_ok())
			{
				String error = model->get_error();
				SDL_Log(error.c_str());

				model.reset();
				return false;
			}
		}

		return true;
	}
}
