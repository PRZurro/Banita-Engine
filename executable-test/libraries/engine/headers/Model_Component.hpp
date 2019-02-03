/**
 * @file Model_Component.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Component that stores a 3d mesh and process it's information and attributes
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Component.hpp"
#include "Render_Module.hpp"

#include <Model_Obj.hpp>
#include <Material.hpp>

namespace banita
{
	class Model_Component : public Component
	{
		using Model = glt::Model_Obj;
		using Model_sptr = std::shared_ptr<glt::Model_Obj>;

	private:

		Model_sptr model;

	public:

		//static fnComponentGenerator generatorInstance;

	public:

		/**
		 * @brief Construct a new Model_Component object and store the entity received
		 * 
		 * @param _entity 
		 */
		Model_Component(Entity * _entity);

		/**
		 * @brief Construct a new Model_Component object by the current obj path. Currently unavailable the creation of the 3d mesh with this constructor
		 * 
		 * @param entity 
		 * @param _modelPath 
		 */
		Model_Component(Entity * entity, const String & _modelPath);

	public:

		/**
		 * @brief initialize the model component attributes and members
		 * 
		 * @return true 
		 * @return false 
		 */
		bool initialize() override;

		/**
		 * @brief update the model component attributes and members
		 * 
		 * @param _deltaTime 
		 * @return true 
		 * @return false 
		 */
		bool update(float _deltaTime) override;

		/**
		 * @brief parse the xml node parameters and initialize the 3d mesh by the value (name of the file)
		 * 
		 * @param _name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool parse_property(const String & _name, const String & value) override;

	public:

		/**
		 * @brief Get the model shared pointer
		 * 
		 * @return Model_sptr 
		 */
		Model_sptr get_model()
		{
			return model;
		}

	public:

		/**
		 * @brief Model component's generator
		 * 
		 * @param _entity 
		 * @return Component_sptr 
		 */
		static Component_sptr generator(Entity * _entity)
		{
			return Component_sptr(new Model_Component(_entity));
		}
	};
}