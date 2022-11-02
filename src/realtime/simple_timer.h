/*
================================================================================
 DREAM core / Simple timer module
--------------------------------------------------------------------------------

 Simple timer based on Arduino `millis()` function.

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>

namespace dream
{
	class SimpleTimer
	{
		private: //-----------------------------------------------------------------

		// Time typedef
		typedef unsigned long long_time_t;

		// Timer interval
		long_time_t _interval;

		// Run callback function on elapsed
		bool _callback_on_elapsed = false;

		// Timer cycle start
		long_time_t _start_time;

		// Callback function
		typedef void (*CallbackFunction)(SimpleTimer*);
		CallbackFunction _callback_function;

		public: //------------------------------------------------------------------

		// Timer constructor
		SimpleTimer(long_time_t interval = 1000) : _interval(interval) { }

		SimpleTimer(long_time_t interval, CallbackFunction f) : _interval(interval) 
		{ 
			onElapsed(f);
		}

		// Begin timer 
		void begin()
		{
			reset();
		}

		// Begin with interval setting
		void begin(long_time_t new_interval)
		{
			setInterval(new_interval);
			reset();
		}

		// Reset timer
		void reset() 
		{
			_start_time = millis();
		}

		// Set timer interval
		void setInterval(long_time_t new_interval)
		{
			_interval = new_interval;
		}

		// Check trigger
		bool check() const
		{
			long_time_t current_millis = millis();

			return ((current_millis - _start_time) > _interval);
		}

		// Function to call on elapsed
		void onElapsed(CallbackFunction f)
		{
			_callback_on_elapsed = true;
			_callback_function = f;
		}

		// Check timer and run callback
		void tick()
		{
			if (_callback_on_elapsed && check()) _callback_function(this);
		}

		// The number of milliseconds until the next trigger
		long_time_t remains() const
		{
			long_time_t current_millis = millis();

			return ((_start_time + _interval) - current_millis);
		}

		// The number of milliseconds that have passed since the last reset
		long_time_t passed() const
		{
			long_time_t current_millis = millis();

			return current_millis - _start_time;
		}
	};
}
