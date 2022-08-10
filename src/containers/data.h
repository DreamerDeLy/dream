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

#pragma once

#include <Arduino.h>

#include <vector>

#include "value.h"
#include "null_defines.h"

namespace dream
{
	class Data
	{
	public:
		// VALUES
		std::vector<Value> values;

		Data() {}

		// Add one value to values list
		void addValue(Value value);

		// Add list of values to values list
		void addValues(std::vector<Value> values);

		// Erase values from array
		void eraseValues();

		// Find first value that match the template
		Value* find(String type, String unit = NULL_STR, String sensor = NULL_STR);

		// Check if values array contains specific value
		bool contains(String type, String unit = NULL_STR, String sensor = NULL_STR) const;

		// Print list of values to string
		String toString() const;

		// Calculate AVG values from array of Data
		static Data calculateAvg(std::vector<Data> data_arr);

		private:

		// Find first value that match the template and return index
		int indexOf(String type, String unit = NULL_STR, String sensor = NULL_STR);
	};

}

