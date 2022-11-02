/*
================================================================================
 DREAM core / Simple stopwatch module
--------------------------------------------------------------------------------

 Simple module for calculating the time of execution of some functions based on 
 Arduino `millis()` function.

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>

namespace dream
{
	class SimpleStopwatch
	{
		private:
		unsigned long _start_time = millis();

		public:
		SimpleStopwatch() {}

		// Start calculation
		void start()
		{
			_start_time = millis();
		}

		// Get elapsed time
		unsigned long getTime() const
		{
			return (millis() - _start_time);
		}
	};	
}
