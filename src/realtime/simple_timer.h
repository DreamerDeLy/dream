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

class SimpleTimer
{
	private: //-----------------------------------------------------------------
	typedef unsigned long long_time_t;

	long_time_t _interval;
	long_time_t _last_tick = millis();

	public: //------------------------------------------------------------------

	// Timer constructor
	SimpleTimer(long_time_t interval = 1000) : _interval(interval) { }

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
		_last_tick = millis();
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

		return ((current_millis - _last_tick) > _interval);
	}

	// The number of milliseconds until the next trigger
	long_time_t remains() const
	{
		long_time_t current_millis = millis();

		return ((_last_tick + _interval) - current_millis);
	}

	// The number of milliseconds that have passed since the last reset
	long_time_t passed() const
	{
		long_time_t current_millis = millis();

		return current_millis - _last_tick;
	}
};


