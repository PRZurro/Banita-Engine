/**
* @file Message.hpp
*
* @author Pablo Rodr�guez Zurro
*
* @date 28/12/2018
*
* @class Message
*
* @brief class in charge of save information that is necessary to reach another class inherited from listener
*/

#pragma once

#include <declarations.hpp>
#include <unordered_map>

namespace banita
{
	constexpr auto KEY_PRESSED_ID = "key pressed";
	class Message
	{
	public:
		using Properties = std::unordered_map<Int32, Var>;

	private:
		//variables
		Int32 ID;					  // hash of a string
		Properties messageProperties; // unordered map of properties

	public:
		//Constructors / Destructors
		Message();
		Message(Int32 _id) : ID(_id) {}
		Message(String _idString) : ID(FNV32(_idString)) {}

		~Message()
		{
			messageProperties.clear();
		}
	public:
		/**
			 * @brief adds a property from the content of the message and it's hashed value
			 * 
			 * @param _key hashed value of the content to add
			 * @param _property  current value of the content to add
			 */
		void add_property(String _key, Var & _property)
		{
			Int32 key = FNV32(_key);

			messageProperties[FNV32(_key)] = &_property;
		}

	/*	void add_property(String _key, String _property)
		{
			SDL_log(FNV32(_key));
			messageProperties[FNV32(_key)] = _property;
		}*/

		/**
			 * @brief Removes a property in a located key
			 * 
			 * @param _key 
			 */
		void remove_property(String &_key)
		{
			messageProperties.erase(FNV32(_key));
		}

	public:
		/**
		 * @brief returns a constant refence to a message property 
		 * 
		 * @param _key 
		 * @return Variant& 
		 */
		const Variant & get_property(String &_key) 
		{
			return messageProperties[FNV32(_key)];
		}

		/**
		 * @brief Get the properties object
		 * 
		 * @return const Properties& 
		 */
		const Properties & get_properties() const
		{
			return messageProperties;
		}

		/**
		 * @brief Get the id object
		 * 
		 * @return Int32 
		 */
		Int32 get_id() const
		{
			return ID;
		}

	public:
		
		/**
		 * @brief operator that returns a property stored in a given _key
		 * 
		 * @param _key 
		 * @return Variant& 
		 */
		Variant & operator[](const Int32 _key)
		{
			return messageProperties[_key];
		}

		/**
		 * @brief operator that returns a property stored in a given unhashed _key
		 * 
		 * @param _key 
		 * @return Variant& 
		 */
		Variant & operator[](const String & _key)
		{
			return messageProperties[FNV32(_key)];
		}

		/**
		 * @brief when an instance of this class is treated as an uint32_t returns the message's id
		 * 
		 * @return Int32 
		 */
		operator Int32() const
		{
			return ID;
		}

		/**
		 * @brief when an instance of this class is treated as an unordered map <Int32, Var> returns the message properties object
		 * 
		 * @return Properties 
		 */
		operator Properties() const
		{
			return messageProperties;
		}

		bool operator == (const Message & _other) const
		{

			if (ID == _other.ID && messageProperties.size() == _other.messageProperties.size()) // if the messages ids and properties map sizes are the same, could be the same content..
			{
				auto iterator = messageProperties.begin(), iterator2 = _other.messageProperties.begin(); // initialized the iterators to iterate over the properties of the messages

				String tempS1 = "", tempS2 = "";
 
				for (iterator; iterator != messageProperties.end() && iterator2 != _other.messageProperties.end(); ++iterator, ++iterator2)
				{
					tempS1 = iterator->second; 
					tempS2 = iterator2->second;
					if (iterator->first != iterator2->first || tempS1 != tempS2) // cant compare two vars without converting them to string (or another type) previously
					{
						return false;
					}
				}

				return true;
			}
			return false;
		}

		bool operator != (const Message & _other) const
		{
			return !(this == &_other);
		}
	};

	
} 
