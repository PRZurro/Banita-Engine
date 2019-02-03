/**
 * @file Controller.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Virtual class of the controller component. A controller is a component and a listener at the same time. 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "declarations.hpp"
#include "Component.hpp"
#include "Message_Handler.hpp"

namespace banita
{
	class Controller : public Component , public Message_Handler::Listener
	{

	protected:

		Message_Handler * messageHandler; // to have access to the possible messages sended to this listener 
		std::list<Message> messages; // to subscribe a message and handle it when triggered

	protected:

		/**
		 * @brief Construct a new Controller object by default
		 * 
		 */
		Controller();

		/**
		 * @brief Construct a new Controller object by the received attributes
		 * 
		 * @param _owner 
		 * @param _mh 
		 * @param _type 
		 * @param _name 
		 */
		Controller(Entity * _owner, Message_Handler * _mh = nullptr, String _type = "undefined", String _name = "undefined");

		/**
		 * @brief Destroy the Controller object and the messages that stores. 
		 * 
		 */
		virtual ~Controller()
		{
			messages.clear();
		}

	public:

		/**
		 * @brief component's legacy method. Initialize the component properties and variables.
		 * 
		 * @return true 
		 * @return false 
		 */
		virtual bool initialize() override = 0;

		/**
		 * @brief component's legacy method. Update the component properties and variables. 
		 * 
		 * @param _deltaTime 
		 * @return true 
		 * @return false 
		 */
		virtual bool update(float _deltaTime) override = 0;
	
		/**
		 * @brief component's legacy method. Parse an xml node property: E.g.: name: position and value: 0,0,0
		 * 
		 * @param _name 
		 * @param _value 
		 * @return true 
		 * @return false 
		 */
		virtual bool parse_property(const String & _name, const String & _value) override = 0;
		
		/**
		 * @brief Listener's legacy method. When triggered, the message is proccesed, producing an action. 
		 * 
		 * @param _message 
		 */
		virtual void handle(const Message & _message) override = 0;
		
		/**
		 * @brief When this controller is going to be deleted, do something
		 * 
		 */
		virtual void on_stop() = 0;
		
		/**
		 * @brief subscribe the messages of this controller to the Message Handler 
		 * 
		 */
		void subscribe_messages();
		
		/**
		 * @brief add a message to the message list of this controller 
		 * 
		 * @param _message 
		 */
		void add_message(Message & _message);

		/**
		 * @brief set the message handler to this controller
		 * 
		 * @param _mh 
		 */
		void set_message_handler(Message_Handler * _mh)
		{
			messageHandler = _mh;
		}
	};
}