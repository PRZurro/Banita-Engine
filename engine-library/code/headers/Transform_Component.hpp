/**
 * @file Transform_Component.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Component in charge of process the transformation matrices(position, scale, rotation) and the visibility of the children's node and parent's logic
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "declarations.hpp"
#include "Component.hpp"

#include "Node.hpp"
#include "glm/glm.hpp"

#include <unordered_map>

namespace banita 

{
	class Transform_Component : public Component
	{
		using Transformation_Matrix = Matrix44;

	private:

		Transform_Component * parent;

		Transformation_Matrix local_scale;
		Transformation_Matrix local_anchor;
		Transformation_Matrix transformation;

		std::vector<Vector3f> movementList;
		
		bool visible;
		
	public:

		/**
		 * @brief Construct a new Transform_Component object and store the received entity
		 * 
		 * @param _owner 
		 */
		Transform_Component(Entity * _owner);


		/**
		 * @brief Destroy the Transform_Component object
		 * 
		 */
		~Transform_Component() override
		{
		}

	public:

		/**
		 * @brief 
		 * 
		 * @return true 
		 * @return false 
		 */
		bool initialize() override;

		/**
		 * @brief 
		 * 
		 * @param _deltaTime 
		 * @return true 
		 * @return false 
		 */
		bool update(float _deltaTime) override;

		/**
		 * @brief 
		 * 
		 * @param _name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool parse_property(const String & _name, const String & value) override;

	public:

		/**
		 * @brief returns if a coordinate is nearest to a coordinate than the limit tridimensional distance. It can despise the desired axis 
		 * 
		 * @param _coordinate 
		 * @param _tridimensionalDistance 
		 * @param _despiseX 
		 * @param _despiseY 
		 * @param _despiseZ 
		 * @return true 
		 * @return false 
		 */
		bool is_near_to_coordinate(Vector3f _coordinate, float _tridimensionalDistance, bool _despiseX = false, bool _despiseY = false, bool _despiseZ = false)
		{
			Vector3f thisPosition = get_position();
			_tridimensionalDistance = std::abs(_tridimensionalDistance); // it has to be positive
			float dX = 0.f, dY = 0.f, dZ = 0.f;

			if (!_despiseX)
				dX = std::pow(_coordinate.x - thisPosition.x, 2);
			if (!_despiseY)
				dY = std::pow(_coordinate.y - thisPosition.y, 2);
			if(!_despiseZ)
				dZ = std::pow(_coordinate.z - thisPosition.z, 2);

			bool toReturn = (std::sqrt(dX + dY + dZ) <= _tridimensionalDistance);

			return toReturn;
		}

		/**
		 * @brief return if the received transform is nearest to this than the limit tridimensional distance. It can despise the desired axis
		 * 
		 * @param _other 
		 * @param _tridimensionalDistance 
		 * @param _despiseX 
		 * @param _despiseY 
		 * @param _despiseZ 
		 * @return true 
		 * @return false 
		 */
		bool is_near_to_transform(Transform_Component & _other, float _tridimensionalDistance, bool _despiseX = false, bool _despiseY = false, bool _despiseZ = false)
		{
			return is_near_to_coordinate(_other.get_position(), _tridimensionalDistance, _despiseX,  _despiseY,  _despiseZ);
		}

	public:

		/**
		 * @brief Get the position vector
		 * 
		 * @return Vector3f 
		 */
		Vector3f get_position()
		{
			return glt::extract_translation(transformation);
		}

		/**
		 * @brief Get the rotation vector
		 * 
		 * @return glt::Quaternion 
		 */
		glt::Quaternion get_rotation()
		{
			return glt::extract_rotation(transformation);
		}

	/*	Vector3f get_scale()
		{
			return glt::extract_scale(transformNode->get_transformation());
		}*/

		/**
		 * @brief Get the transformation matrix
		 * 
		 * @return Matrix44 
		 */
		Matrix44 get_transformation()
		{
			return transformation;
		}

		/**
		 * @brief Get the local anchor matrix
		 * 
		 * @return Matrix44 
		 */
		Matrix44 get_local_transformation()
		{
			return local_anchor;
		}

		/**
		 * @brief Get the parent transform component
		 * 
		 * @return Transform_Component* 
		 */
		Transform_Component * get_parent()
		{
			return parent;
		}

	public:

		/**
		 * @brief move this transform
		 * 
		 * @param _translation 
		 */
		void move(Vector3f & _translation)
		{
			transformation = glt::translate(transformation,_translation);
		}

		/**
		 * @brief move this transform by a movement list 
		 * 
		 * @param _movementList 
		 */
		void move(std::vector<Vector3f> & _movementList)
		{	
			Vector3f resultantMovement(0.f,0.f,0.f); 


			for (Vector3f & _movement : _movementList)
			{
				resultantMovement += _movement;
			}

			move(resultantMovement);
		}
		
		/**
		 * @brief add a movement to the accumulated move list
		 * 
		 * @param _translation 
		 */
		void add_movement(Vector3f _translation)
		{
			movementList.push_back(_translation);
		}

		/**
		 * @brief rotate this transform by the received vector
		 * 
		 * @param _rotation 
		 */
		void rotate(Vector3f & _rotation)
		{
			rotate(_rotation.x, _rotation.y, _rotation.z);
		}

		/**
		 * @brief rotate this transform by the received values
		 * 
		 * @param _x 
		 * @param _y 
		 * @param _z 
		 */
		void rotate(float _x, float _y, float _z)
		{
			transformation = glt::rotate_around_x(transformation, _x);
			transformation = glt::rotate_around_y(transformation, _y);
			transformation = glt::rotate_around_z(transformation, _z);
		}

		/**
		 * @brief rotate this transform rotation x component
		 * 
		 * @param _rotX 
		 */
		void rotateX(float _rotX)
		{
			rotate(_rotX, 0.f, 0.f);
		}

		/**
		 * @brief rotate this transform rotation y component
		 * 
		 * @param _rotY 
		 */
		void rotateY(float _rotY)
		{
			rotate(0.f, _rotY, 0.f);
		}

		/**
		 * @brief rotate this transform rotation z component
		 * 
		 * @param _rotZ 
		 */
		void rotateZ(float _rotZ)
		{
			rotate(0.f, 0.f, _rotZ);
		}

		/**
		 * @brief scale this transform by the input value
		 * 
		 * @param _value 
		 */
		void scale(float _value)
		{
			transformation = glt::scale(transformation,_value);
		}

		/**
		 * @brief Set the transform position to the received vector
		 * 
		 * @param _position 
		 */
		void set_position(Vector3f & _position)
		{
			Vector3f translationV = glt::extract_translation(transformation);
			Vector3f tempTranslationV = Vector3f(translationV.x - _position.x, translationV.y - _position.y, translationV.z - _position.z);

			transformation = glt::translate(transformation, tempTranslationV);
		}
		
		/**
		 * @brief Set the position to the received values
		 * 
		 * @param _pX 
		 * @param _pY 
		 * @param _pZ 
		 */
		void set_position(float _pX, float _pY, float _pZ)
		{
			Vector3f position = Vector3f(_pX, _pY, _pZ);
			set_position(position);
		}

		/**
		 * @brief Set the position x to the received value
		 * 
		 * @param _pX 
		 */
		void set_positionX(float _pX)
		{
			set_position(_pX, 0.0f, 0.0f);
		}

		/**
		 * @brief Set the position y to the received value
		 * 
		 * @param _pY 
		 */
		void set_positionY(float _pY)
		{
			set_position(0.0f, _pY, 0.0f);
		}

		/**
		 * @brief Set the position z to the received value
		 * 
		 * @param _pZ 
		 */
		void set_positionZ(float _pZ)
		{
			set_position(0.0f, 0.0f, _pZ);
		}

		/**
		 * @brief Set if is visible this transform (and children)
		 * 
		 * @param _visibility 
		 */
		void set_visible(bool _visibility)
		{
			visible = _visibility;
		}

		/**
		 * @brief Get the visibility object
		 * 
		 * @return true 
		 * @return false 
		 */
		bool get_visibility()
		{
			return visible;
		}

		/**
		 * @brief reset the transformation of this component
		 * 
		 */
		void reset()
		{
			transformation = local_anchor * local_scale;
		}

		/**
		 * @brief generator of this component
		 * 
		 * @param _entity 
		 * @return Component_sptr 
		 */
		static Component_sptr generator(Entity * _entity)
		{
			return Component_sptr(new Transform_Component(_entity));
		}

	};
}