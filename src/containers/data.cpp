/*
================================================================================
 DREAM core / Data module
--------------------------------------------------------------------------------

 A module of the Data class that can store and process a set of Value objects.

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

// Header
#include "data.h"

using namespace dream;

//-----------------------------------------------------------------------------+
// Add one value to values list
//-----------------------------------------------------------------------------+
void Data::addValue(Value value)
{
	if (contains(value.type, value.unit, value.sensor))
	{
		// Replace existing value
		values[indexOf(value.type, value.unit, value.sensor)] = value;
	}
	else
	{
		// Add new value
		values.push_back(value);
	}
}

//-----------------------------------------------------------------------------+
// Add list of values to values list
//-----------------------------------------------------------------------------+
void Data::addValues(std::vector<Value> values)
{
	for (Value &value : values)
	{
		addValue(value);
	}
}

//-----------------------------------------------------------------------------+
// Erase values
//-----------------------------------------------------------------------------+
void Data::eraseValues()
{
	values.erase(values.begin(), values.end());
}

//-----------------------------------------------------------------------------+
// Find first value that match the template
// Returns: pointer to the Value object or nullptr if Value not found
//-----------------------------------------------------------------------------+
Value* Data::find(String type, String unit /*= NULL_STR*/, String sensor /*= NULL_STR*/) 
{
	// Find index of value
	int i = indexOf(type, unit, sensor);

	// If value exist
	if (i >= 0)
	{
		// Return pointer to value
		return &values[i];
	}
	else
	{
		// Return NULL value
		return nullptr;
	}
}

//-----------------------------------------------------------------------------+
// Find index of first value that match the template
// Returns: index of the Value or -1 if value not found
//-----------------------------------------------------------------------------+
int Data::indexOf(String type, String unit /*= NULL_STR*/, String sensor /*= NULL_STR*/)
{
	for (int i = 0; i < values.size(); i++)
	{
		const Value &v = values[i];

		if ((v.type == type) && (v.unit == unit || unit == NULL_STR) && (v.sensor == sensor || sensor == NULL_STR))
		{
			return i;
		}
	}

	return -1;
}

//-----------------------------------------------------------------------------+
// Check if values array contains specific value
//-----------------------------------------------------------------------------+
bool Data::contains(String type, String unit /*= NULL_STR*/, String sensor /*= NULL_STR*/) const
{
	for (const Value &v : values)
	{
		if ((v.type == type) && (v.unit == unit || unit == NULL_STR) && (v.sensor == sensor || sensor == NULL_STR))
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------+
// Print list of values to string
//-----------------------------------------------------------------------------+
String Data::toString() const
{
	String s = "";

	if (values.size() > 0)
	{
		for (const Value &v : values)
		{
			s += " - " + v.toString() + "\r\n";
		}
	}
	else
	{
		s = String(" <none>") + "\r\n";
	}

	return s;
}

//-----------------------------------------------------------------------------+
// Calculate AVG values from array of Data
//-----------------------------------------------------------------------------+
Data Data::calculateAvg(std::vector<Data> data_arr)
{
	// Copy all data except values
	Data result = data_arr[0];
	result.values.clear();

	// Structure for recording the number of sums
	struct AvgCounter
	{
		String type;
		String unit;
		String sensor;
		int counter;

		bool belongsToValue(const Value& v) const
		{
			return (this->type == v.type && this->unit == v.unit && this->sensor == v.sensor);
		}
	};

	std::vector<AvgCounter> avg_counters;

	// Processing all Data items in list
	for (const Data &d : data_arr)
	{
		// Processing all values in Data
		for (const Value &v : d.values)
		{
			if (!result.contains(v.type, v.unit, v.sensor))
			{
				// Add AVG counter
				avg_counters.push_back({v.type, v.unit, v.sensor, (v.isNull() ? 0 : 1)});

				// Copying value to result
				Value avg_value = Value(v);
				result.addValue(avg_value);
			}
			else
			{
				if (!v.isNull())
				{
					// Find value in result Data
					Value *avg_value = result.find(v.type, v.unit, v.sensor);

					// First value have to be zero for correct summation
					if (avg_value->isNull() && avg_value->isNumeric()) avg_value->setValue(0);

					if (v.data_type == ValueDataType::Float)
					{
						// Save decimal_places and set to 2 for more accurate averaging
						int decimal_places = v.decimal_places > 0 ? v.decimal_places : 2;

						// Summation
						avg_value->setValue(avg_value->asFloat() + v.asFloat(), decimal_places);
					}
					else if (v.data_type == ValueDataType::Int)
					{
						// Summation
						avg_value->setValue(avg_value->asInt() + v.asInt());
					}
					else
					{
						// Strings cannot be averaged
						avg_value->setValue(v.asString());
					}

					// Increment counter
					for (AvgCounter& a : avg_counters)
					{
						if (a.belongsToValue(v)) a.counter++;
					}
				}
			}
		}
	}

	// Divide by the counter to get the average
	for (Value &v : result.values)
	{
		if (!v.isNull())
		{
			// Counter for division
			int avg_counter = 1;
			
			// Find counter
			for (AvgCounter& a : avg_counters)
			{
				if (a.belongsToValue(v)) avg_counter = a.counter;
			}

			if (v.data_type == ValueDataType::Float)
			{
				// Set to 2 for more accurate averaging
				int decimal_places = (v.decimal_places > 0 ? v.decimal_places : 2);
				v.setValue(v.asFloat() / avg_counter, decimal_places);
			}
			else if (v.data_type == ValueDataType::Int)
			{
				// Set as float for more accurate averaging 
				v.setValue(v.asFloat() / avg_counter, 2);
			}
		}
	}

	return result;
}