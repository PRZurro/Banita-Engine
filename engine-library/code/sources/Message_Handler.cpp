
#include "Message_Handler.hpp"

namespace banita
{


	//Message_Handler * Message_Handler::inst;

	void Message_Handler::singlecast(Int32 id, const Message & _message)
	{
		if (singlecastTargets.count(_message.get_id()) != 0)
		{
			auto iterator = singlecastTargets.find(id);

			if (iterator != singlecastTargets.end())
			{
				iterator->second->handle(_message);
			}
		}
	}

	void Message_Handler::multicast(const Message & _message)
	{
		if (!is_message_blocked(_message))
		{
			auto iterator = multicastTargets.find(_message.get_id());

			if (iterator != multicastTargets.end())
			{
				for (auto & listener : iterator->second)
				{
					listener->handle(_message);
				}
			}
		}
	}
}