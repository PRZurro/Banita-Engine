#pragma once


#include "declarations.hpp"
#include "Controller.hpp"
#include "Message.hpp"

namespace banita
{
	class Player_Controller : public Controller
	{
	private:

		//static fnControllerComponentGenerator generatorInstance;

		Message * moveUp, * moveDown,  * moveLeft, * moveRight;  // Created to ease of use.
		int turn; // "Game Controller" needed variable
		bool limits; // "Game Controller" needed variable


	protected:

		Player_Controller(Entity * _entity, Message_Handler * _mh, String _type = "playercontroller", String _name = "undefined");
		Player_Controller();

	public:

		 bool initialize() override;
		 bool update(float _deltaTime) override;
		 bool parse_property(const String & _name, const String & _value) override;
		 void handle(const Message & _message) override;
		 void on_stop();


	public:

		static Component_sptr generator(Entity * _entity, Message_Handler * _mh )
		{
			Component * controller = new Player_Controller(_entity, _mh);
			return Component_sptr(controller);
		}

	private:

		void create_messages();
		void game_controller(); // This method should be in a game controller component script and shoulds communicates with 
	};
}