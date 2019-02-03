/**
 * @file Message_Handler.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Process and save the messages and listeners 
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "Message.hpp"
#include "SDL_log.h"

namespace banita
{
	//static const String KEY_PRESSED; 

	class Message_Handler
	{
	public: 

		/**
		 * @brief almost empty pure virtual struct that let the children handle a received message
		 * 
		 */
		struct Listener
		{
		public:

			/**
			 * @brief Destroy the Listener object
			 * 
			 */
			virtual ~Listener() {}

		public:

			/**
			 * @brief handle the received message
			 * 
			 * @param _message 
			 */
			virtual void handle(const Message & _message) = 0;
		};

	private:

		using Listener_List = std::list<Listener*>;
		using Listener_Map = std::unordered_map< Int32, Listener * >;
		using Listener_List_Map = std::unordered_map< Int32, Listener_List >;

	private:
		
		Listener_Map singlecastTargets; // ID map that stores one listener per message
		Listener_List_Map multicastTargets; // ID map that stores multiple listener per message

		std::unordered_map < Int32, std::list< Message >> blockedMessages; //Same message can have different attributes but same id

		//static Message_Handler * inst;

	public: 
		
		/**
		 * @brief Construct a new Message_Handler object by default
		 * 
		 */
		Message_Handler()
		{
			singlecastTargets = {  };
			multicastTargets = {   };
			blockedMessages = {    };
		}
		
		/**
		 * @brief Destroy the Message_Handler object and empty the maps 
		 * 
		 */
		~Message_Handler()
		{
			singlecastTargets.clear();

			auto iterator = multicastTargets.begin();

			for(iterator; iterator != multicastTargets.end(); ++iterator)
			{
				iterator->second.clear();
			}

			auto iteratorBlocked = blockedMessages.begin();

			for (iterator; iteratorBlocked != blockedMessages.end(); ++iteratorBlocked)
			{
				iterator->second.clear();
			}

			multicastTargets.clear();
		}

	public:

		/**
		 * @fn	void Message_Handler::add_singlecast_listener(Int32 listener_id, Listener & _listener)
		 *
		 * @brief	Adds a listener to the listeners map singlecastTargets with the given listener id. 
		 *
		 * @param 		  	listener_id	Identifier for the listener.
		 * @param [in,out]	_listener  	The listener.
		 */
		void add_singlecast_listener(Int32 listener_id, Listener * _listener)
		{
			singlecastTargets[listener_id] = _listener;
		}

		/**
		 * @fn	void Message_Handler::add_multicast_listener(Int32 message_id, Listener & _listener)
		 *
		 * @brief	Adds a listener to an specific message id list of listeners.
		 *
		 * @param 		  	message_id	Identifier for the message.
		 * @param [in,out]	_listener 	The listener.
		 */
		void add_multicast_listener(Int32 message_id, Listener * _listener)
		{
			if (multicastTargets.count(message_id) != 0)
			{
				auto iteratorBegin = std::find(multicastTargets[message_id].begin(), multicastTargets[message_id].end(), _listener);
				auto iteratorEnd = multicastTargets[message_id].end();

				if( iteratorBegin != iteratorEnd)
					return;
			}
			multicastTargets[message_id].push_back(_listener);
		}

		void block_message(Message _message)
		{
			blockedMessages[_message.get_id()].push_back(_message);
		}

		void unblock_message(Message _message)
		{
			bool unblocked = false;

			for (auto iterator = blockedMessages[_message.get_id()].begin() ; iterator != blockedMessages[_message.get_id()].end() ; ++iterator)
			{
				if (_message == *iterator)
				{
					unblocked = true;
					iterator = blockedMessages[_message.get_id()].erase(iterator);	
					/*iterator._Orphan_me();*/
					break; // Unknown error
				}
			}
		}

		/**
		 * @brief check if the input message is in the blocked messages map  
		 * 
		 * @param _message 
		 * @return true 
		 * @return false 
		 */
		bool is_message_blocked(const Message & _message)
		{
			auto iterator = blockedMessages[_message.get_id()].begin(), end = blockedMessages[_message.get_id()].end();
			
			bool found = false;
			for (iterator; iterator != end && !found; ++iterator)
			{
				if (*iterator == _message)
				{
					return true;
				}
			}

			return false;
		}

		/**
		 * @fn	void Message_Handler::singlecast(Int32 id, const Message & _message)
		 *
		 * @brief	Check if there it is a pending message for an specific listener id. If it is a message for the listener, let it handle the message. 
		 *
		 * @param	id			The identifier.
		 * @param	_message	The message.
		 */
		void singlecast(Int32 id, const Message & _message);
		
		/**
		 * @fn	void Message_Handler::multicast(const Message & _message)
		 *
		 * @brief	Check if there it is a pending message. If it is, let the subscribed listeners handle the message.
		 *
		 * @param	_message	The message.
		 */
		void multicast(const Message & _message);
		
	};
}