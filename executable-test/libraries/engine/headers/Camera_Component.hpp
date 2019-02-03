/**
 * @file Camera_Component.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Camera component
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Component.hpp"
#include "Camera.hpp"

#define DEFAULT_FOV 90.0f
#define DEFAULT_ASPECT_RATIO  1.77777777778f
#define DEFAULT_NEAR_PLANE_DISTANCE 0.3f
#define DEFAULT_FAR_PLANE_DISTANCE 900.f

namespace banita
{
	class Camera_Component : public Component
	{
		using Camera = glt::Camera;
		using Camera_sptr = std::shared_ptr<glt::Camera>;

	private:

		Camera_sptr camera; // Shared pointer to a opengl-toolkit camera object
		
	public:

		//static fnComponentGenerator generatorInstance;

	public:
		/**
		 * @brief Construct a new Camera_Component object
		 * 
		 * @param _owner 
		 * @param _fov 
		 * @param _aspectRatio 
		 * @param nearPlaneD 
		 * @param _farPlaneD 
		 */
		Camera_Component(Entity * _owner,
			float _fov = DEFAULT_FOV,
			float _aspectRatio = DEFAULT_ASPECT_RATIO,
			float nearPlaneD = DEFAULT_NEAR_PLANE_DISTANCE,
			float _farPlaneD = DEFAULT_FAR_PLANE_DISTANCE
		);

	public:
		/**
		 * @brief initialize the camera component objects and logic
		 * 
		 * @return true 
		 * @return false 
		 */
		bool initialize() override;

		/**
		 * @brief update frame to friend the camera component objects and logic
		 * 
		 * @param _deltaTime 
		 * @return true 
		 * @return false 
		 */
		bool update(float _deltaTime) override;

		/**
		 * @brief parse the properties of the camera, currently unavailable
		 * 
		 * @param _name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool parse_property(const String & _name, const String & value) override;

	public:

		/**
		 * @brief Get the camera object
		 * 
		 * @return Camera_sptr 
		 */
		Camera_sptr get_camera()
		{
			return camera;
		}

	public:

		/**
		 * @brief Generator of camera component
		 * 
		 * @param _entity 
		 * @return Component_sptr 
		 */
		static Component_sptr generator(Entity * _entity)
		{
			return Component_sptr(new Camera_Component(_entity));
		}
	};
}