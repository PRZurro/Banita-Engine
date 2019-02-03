#pragma once

#include "Player_Controller.hpp"
#include "Component_Generator.hpp"
#include "Entity.hpp"
#include "Message_Handler.hpp"
#include "Transform_Component.hpp"
#include "glm/glm.hpp"


namespace banita
{
	//fnControllerComponentGenerator Player_Controller::generatorInstance = Component_Generator::get_instance()->register_controller("playercontroller",Player_Controller::generator);

	Player_Controller::Player_Controller(Entity * _entity, Message_Handler * _mh, String _type, String _name) 
		: Controller(_entity, _mh, _type, _name)
	{
		create_messages();
		turn = 1;
		limits = true;
	}

	Player_Controller::Player_Controller() : Controller()
	{
		create_messages();
	}

	bool Player_Controller::initialize()
	{
		if (messageHandler)
		{
			subscribe_messages();
			return true;
		}
		return false;
	}
	bool Player_Controller::update(float _deltaTime)
	{
		game_controller(); // Yes, this has not to be here
		return false;
	}
	bool Player_Controller::parse_property(const String & _name, const String & _value)
	{
		return false;
	}
	void Player_Controller::handle(const Message & _message)
	{
		Int32 messageID = _message.get_id();

		String keypressedS = KEY_PRESSED_ID;

		Int32 keypressedI = FNV32(keypressedS);

		if (keypressedI == messageID)
		{
			Vector3f movement = Vector3f(0.f, 0.f, 0.f);

			if (*moveUp == _message)
			{
				movement.y = 0.2f; // Multiply by a speed and deltatime in the update
			}
			else if (*moveDown == _message)
			{
				movement.y = -0.2f;
			}
			else if (*moveRight == _message)
			{
				movement.x = 0.2f;
			}
			else if (*moveLeft == _message)
			{
				movement.x = -0.2f;
			}

			owner->get_transform().move(movement);

			Vector3f vector = owner->get_transform().get_position();


			String position = "X:  " + std::to_string(vector.x) + "  Y:  " + std::to_string(vector.y) + "   Z:  " + std::to_string(vector.z);

			SDL_Log(position.c_str());
		}
		
	}
	void Player_Controller::on_stop()
	{
	}
	void Player_Controller::create_messages()
	{
		String keypressedS = KEY_PRESSED_ID;
		
		Var temp = "up";
		messages.push_back(Message(keypressedS));
		moveUp = &messages.back();
		moveUp->add_property("up", temp);

		temp = "up";
		messages.push_back(Message(keypressedS));
		moveDown = &messages.back();
		moveDown->add_property("down", temp);

		temp = "up";
		messages.push_back(Message(keypressedS));
		moveLeft = &messages.back();
		moveLeft->add_property("left", temp);

		temp = "up";
		messages.push_back(Message(keypressedS));
		moveRight = &messages.back();
		moveRight->add_property("right", temp);
	}

	void Player_Controller::game_controller()
	{
		//This method shouldn't be here
		String name = "number1";

		Transform_Component * transform1 = &owner->get_scene()->get_entity(name)->get_transform(); // should be in array
		name = "number2";
		Transform_Component * transform2 = &owner->get_scene()->get_entity(name)->get_transform();
		name = "number3";
		Transform_Component * transform3 = &owner->get_scene()->get_entity(name)->get_transform();
		name = "number4";
		Transform_Component * transform4 = &owner->get_scene()->get_entity(name)->get_transform();
		name = "number5";
		Transform_Component * transform5 = &owner->get_scene()->get_entity(name)->get_transform();
		name = "number6";
		Transform_Component * transform6 = &owner->get_scene()->get_entity(name)->get_transform();
		name = "e_player";
		Transform_Component * transformRex = &owner->get_scene()->get_entity(name)->get_transform();
		name = "wall-up";
		Transform_Component * transformWallUp = &owner->get_scene()->get_entity(name)->get_transform(); // should be in array
		name = "wall-down";
		Transform_Component * transformWallDown = &owner->get_scene()->get_entity(name)->get_transform();
		name = "wall-left";
		Transform_Component * transformWallLeft = &owner->get_scene()->get_entity(name)->get_transform();
		name = "wall-right";
		Transform_Component * transformWallRight = &owner->get_scene()->get_entity(name)->get_transform();

		if (limits)
		{
			if (transformRex)
			{
				if (transformWallUp)
				{
					if (transformRex->is_near_to_transform(*transformWallUp, 0.5f, true))
					{
						owner->get_scene()->get_message_handler()->block_message(*moveUp);
					}
					else
					{
						owner->get_scene()->get_message_handler()->unblock_message(*moveUp);
					}
				}
				if (transformWallDown)
				{
					SDL_Log("found");
					if (transformRex->is_near_to_transform(*transformWallDown, 0.5f, true))
					{
						owner->get_scene()->get_message_handler()->block_message(*moveDown);
					}
					else
					{
						owner->get_scene()->get_message_handler()->unblock_message(*moveDown);
					}
				}
				if (transformWallLeft)
				{
					SDL_Log("found");
					if (transformRex->is_near_to_transform(*transformWallLeft, 0.5f, false, true))
					{
						owner->get_scene()->get_message_handler()->block_message(*moveLeft);
					}
					else
					{
						owner->get_scene()->get_message_handler()->unblock_message(*moveLeft);
					}
				}
				if (transformWallRight)
				{
					SDL_Log("found");
					if (transformRex->is_near_to_transform(*transformWallRight, 0.5f, false, true))
					{
						owner->get_scene()->get_message_handler()->block_message(*moveRight);
					}
					else
					{
						owner->get_scene()->get_message_handler()->unblock_message(*moveRight);
					}
				}

			}
		}
		switch (turn)
		{
		case 1:
			if (transformRex->is_near_to_transform(*transform1, 0.5f))
			{
				++turn;
				transform1->set_visible(false);
			}
			break;
		case 2:
			if (transformRex->is_near_to_transform(*transform2, 0.5f))
			{
				++turn;
				transform2->set_visible(false);
			}
			break;
		case 3:
			if (transformRex->is_near_to_transform(*transform3, 0.5f))
			{
				++turn;
				transform3->set_visible(false);
			}
			break;
		case 4:
			if (transformRex->is_near_to_transform(*transform4, 0.5f))
			{
				++turn;
				transform4->set_visible(false);
			}
			break;
		case 5:
			if (transformRex->is_near_to_transform(*transform5, 0.5f))
			{
				++turn;
				transform5->set_visible(false);
			}
			break;
		case 6:
			if (transformRex->is_near_to_transform(*transform6, 0.5f))
			{
				++turn;
				transform6->set_visible(false);
			}

			break;

		case 7:
			limits = false;

			if (transformWallUp && transformWallDown && transformWallRight && transformWallLeft)
			{
				transformWallUp->set_visible(false);
				transformWallDown->set_visible(false);
				transformWallRight->set_visible(false);
				transformWallLeft->set_visible(false);
			}
		}
	}
}