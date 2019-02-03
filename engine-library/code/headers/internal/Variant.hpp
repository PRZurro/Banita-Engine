#pragma once

/**
* @file Kernel.hpp
*
* @author Pablo Rodríguez Zurro , Ángel Rodríguez (source from his draft)
*
* @date 28/12/2018
*
* @class Kernel
*
* @brief A "Variant" class that stores 5 types of variables and return one accordingly with the current type.   
*/


#include <string>

class Variant
{
private:

	using String = std::string;

private:

	enum Type
	{
		NULLL,
		BOOL,
		INT,
		FLOAT,
		STRING
	};

	union Value
	{
		bool boolValue;
		int	intValue;
		float floatValue;
		String * stringValue;
	};

	Type type;
	Value value;

public:

	Variant() : type(NULLL) {}

	Variant(bool initializer) : type(BOOL)
	{
		value.boolValue = initializer;
	}

	Variant(int initializer) : type(INT)
	{
		value.intValue = initializer;
	}

	Variant(float initializer) : type(FLOAT)
	{
		value.floatValue = initializer;
	}

	Variant(const String & initializer) : type(STRING)
	{
		value.stringValue = new String(initializer);
	}

	~Variant()
	{
		release();
	}

public:

	void release(Type t = NULLL)
	{
		if (type == STRING) delete value.stringValue;

		type = t;
	}

	bool is_null() const { return type == NULLL; }
	bool is_bool() const { return type == BOOL; }
	bool is_int() const { return type == INT; }
	bool is_float() const { return type == FLOAT; }
	bool isSTRING() const { return type == STRING; }

	int asInt() const
	{
		switch (type)
		{
			case BOOL: return value.boolValue;

			case INT: return value.intValue;

			case FLOAT: return int(value.floatValue);

			case STRING: return std::stoi(*value.stringValue);

			default: return 0;
		}
	}

	float asFloat() const
	{
		switch (type)
		{
			//case BOOL: return float(data.boolValue);
			
			case INT: return float(value.floatValue);

			case FLOAT: return value.floatValue;

			case STRING: return std::stof(*value.stringValue);

			default: return 0.0f;
		}
	}

	String asString() const
	{
		switch (type)
		{
			case INT: return std::to_string(value.intValue);

			case FLOAT: return std::to_string(value.floatValue);

			case STRING: return *value.stringValue;

			default: return String();
		}
	}

	bool asBool() const
	{
		switch (type)
		{
			case BOOL: return value.boolValue;

			case INT: return (value.intValue != 0) ? 1 : 0;

			case FLOAT: return (int(value.floatValue) != 0) ? 1 : 0;

			default: false;
		}
	}

public:

	Variant & operator = (const nullptr_t &)
	{
		release(); 
		return *this;
	}

	Variant & operator = (const Variant & other)
	{
		release(other.type);
		value = other.value;
		return *this;
	}

	Variant & operator = (const bool b)
	{
		release(BOOL);
		value.boolValue = b;
		return *this;
	}

	Variant & operator = (const int i)
	{
		release(INT);
		value.intValue = i;
		return *this;
	}

	Variant & operator = (const float f)
	{
		release(FLOAT);
		value.floatValue = f;
		return *this;
	}

	Variant & operator = (const String & f)
	{
		release(STRING);
		*value.stringValue = f;
		return *this;
	}

public:

	operator int() const
	{
		return this->asInt();
	}

	operator String () const
	{
		return this->asString();
	}

	operator float() const 
	{
		return this->asFloat();
	}

	operator bool() const
	{
		return this->asBool();
	}

	operator nullptr_t() const
	{
		return nullptr;
	}
};