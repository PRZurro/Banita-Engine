#include "Controller.hpp"
#include "Controller_Module.hpp"


namespace banita
{
	Controller::Controller() 
		: Component(), messageHandler(nullptr)
	{}

	Controller::Controller(Entity * _owner, Message_Handler * _mh, String _type, String _name)
		: Component(_owner,_type,_name), messageHandler(_mh)
	{}

	void Controller::subscribe_messages()
	{
		if (messageHandler)
		{
			for (Message & message : messages)
			{
				messageHandler->add_multicast_listener(message, this);
			}
		}
	}
	void Controller::add_message(Message & _message)
	{
		messages.push_back(_message);
		//immediately after add the message it is subscribed in the multicast Listeners map, adding the listener. 
	}
}