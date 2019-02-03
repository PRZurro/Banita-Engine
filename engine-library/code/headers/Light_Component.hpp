/**
 * @file Light_Component.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Light render component
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Component.hpp"
#include "Light.hpp"
#include "glm/glm.hpp"

namespace banita
{
	class Light_Component : public Component
	{
		using Light = glt::Light;
		using Light_sptr = std::shared_ptr<Light>;

	private:

		Light_sptr light; // Open GL toolkit Light node 

	private:

		//static fnComponentGenerator generatorInstance;

	public:

		/**
		 * @brief Construct a new Light_Component object and store the entity received
		 * 
		 * @param _entity 
		 */
		Light_Component(Entity * _entity);

	public:

		/**
		 * @brief initialize the light's attribute and members
		 * 
		 * @return true 
		 * @return false 
		 */
		bool initialize() override;

		/**
		 * @brief update the light's attribute and members
		 * 
		 * @param _deltaTime 
		 * @return true 
		 * @return false 
		 */
		bool update(float _deltaTime) override;

		/**
		 * @brief parse the input property and modify the values of the light
		 * 
		 * @param _name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool parse_property(const String & _name, const String & value) override;

	public:

		/**
		 * @brief Get a shared pointer to the light
		 * 
		 * @return Light_sptr 
		 */
		Light_sptr get_light()
		{
			return light;
		}

	public:

		/**
		 * @brief Set the light's color by the floats received
		 * 
		 * @param _r 
		 * @param _g 
		 * @param _b 
		 */
		void set_color(float _r = 252.0f, float _g = 252.0f, float _b =0.f);

		/**
		 * @brief Set the light's color by the float vector received
		 * 
		 * @param _color 
		 */
		void set_color(Vector3f _color);

		/**
		 * @brief Set the light's intensity
		 * 
		 * @param _intensity 
		 */
		void set_intensity(float _intensity);

	public:

		/**
		 * @brief light component generator
		 * 
		 * @param _entity 
		 * @return Component_sptr 
		 */
		static Component_sptr generator(Entity * _entity)
		{
			return Component_sptr(new Light_Component(_entity));
		}
	};
}
