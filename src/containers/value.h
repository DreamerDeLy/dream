/*
================================================================================
 DREAM core / Value container file
--------------------------------------------------------------------------------

 Module of the Value class, which allows you to save data of various types, 
 saving the name of the sensor, units of measurement and the type of value.

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>
#include "null_defines.h"

namespace dream 
{
	enum class ValueDataType
	{
		Int,
		Float,
		String
	};

	class Value
	{
		private: //-------------------------------------------------------------

		// Value
		int as_int;
		float as_float;
		String as_string;

		public: //--------------------------------------------------------------

		String type;
		String unit;
		String sensor;

		ValueDataType data_type;

		int decimal_places = 0; // For float save

		// Constructors

		Value(const String &type, const String &unit, const String &sensor, String value) :
			type(type), unit(unit), sensor(sensor)
		{ 
			setValue(value); 
		}

		Value(const String &type, const String &unit, const String &sensor, float value, int digits) :
			type(type), unit(unit), sensor(sensor)
		{ 
			setValue(value, digits); 
		}

		Value(const String &type, const String &unit, const String &sensor, int value) :
			type(type), unit(unit), sensor(sensor) 
		{ 
			setValue(value); 
		}

		//---------------------------------------------------------------------+
		// Set value from value of specific type and convert it to string
		//---------------------------------------------------------------------+
		void setValue(const String &value)
		{
			if (value != NULL_STR && value.length() > 0)
			{
				this->data_type = ValueDataType::String;
				this->as_string = value;
			}
			else
			{
				setNull();
			}
		}

		void setValue(const float value, const int digits)
		{
			if (value != NULL_FLOAT && isnan(value) == false)
			{
				this->data_type = ValueDataType::Float;

				this->as_float = value;
				this->decimal_places = digits;

				this->as_int = round(value);
				this->as_string = String(value, digits);
			}
			else
			{
				setNull();
			}
		}

		void setValue(const int value)
		{
			if (value != NULL_INT && isnan(value) == false)
			{
				this->data_type = ValueDataType::Int;

				this->as_int = value;

				this->as_float = value;
				this->as_string = String(value);
			}
			else
			{
				setNull();
			}
		}

		//---------------------------------------------------------------------+
		// Convert value to specific type
		// Returns 0.0 or 0 if value not valid
		//---------------------------------------------------------------------+
		float asFloat() const
		{
			return this->as_float;
		}

		int asInt() const
		{
			return this->as_int;
		}

		String asString() const
		{
			return this->as_string;
		}
		
		//---------------------------------------------------------------------+
		// Set value as null
		//---------------------------------------------------------------------+
		void setNull()
		{
			this->as_int = NULL_INT;
			this->as_float = NULL_FLOAT;
			this->as_string = NULL_STR;
		}

		//---------------------------------------------------------------------+
		// Is value NULL
		//---------------------------------------------------------------------+
		bool isNull() const
		{
			// The as_string always contains data. 
			// While other variables can be empty in case the data type is a string.
			return (as_string == NULL_STR);
		}

		//---------------------------------------------------------------------+
		// Is value type Integer or Float
		//---------------------------------------------------------------------+
		bool isNumeric() const 
		{
			return (data_type == ValueDataType::Float || data_type == ValueDataType::Int);
		}

		//---------------------------------------------------------------------+
		// Generate JSON of value
		//---------------------------------------------------------------------+
		String toJSON() const
		{
			String s = F("{\"type\":\"{t}\",\"unit\":\"{u}\",\"sensor\":\"{s}\",\"value\":\"{v}\"},");

			s.replace("{t}", type);
			s.replace("{u}", unit);
			s.replace("{s}", sensor);
			s.replace("{v}", as_string);

			return s;
		}

		//---------------------------------------------------------------------+
		// Generate string with all data
		//---------------------------------------------------------------------+
		String toString() const
		{
			String dt = "";
			switch (data_type)
			{
				case ValueDataType::Int: dt = "i"; break;
				case ValueDataType::Float: dt = "f"; break;
				case ValueDataType::String: dt = "s"; break;
				default: dt = "null"; break;
			}

			return "[" + sensor + "] " + type + " " + as_string + " " + unit + " (" + dt + ")";
		}
	};

}
