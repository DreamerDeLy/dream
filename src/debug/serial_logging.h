/*
================================================================================
 DREAM core / SerialLog module
--------------------------------------------------------------------------------

 Module for logging into any Stream object using macros that collect data about 
 the file, function, and line number in which it was called.

 Based on https://github.com/dmcrodrigues/macro-logger (MIT license)

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>
#include <vector>
#include <time.h>

namespace dream 
{
	class SerialLog
	{
		private: //-------------------------------------------------------------

		// Outputs to logging in
		static std::vector<Stream*> _outputs;
		
		public: //--------------------------------------------------------------

		// Add output to logging in
		static void addOutput(Stream *stream);

		// Used in macros
		static void _printf(const char* format, ...);
	};

	// Initialize `_outputs`
	std::vector<Stream*> SerialLog::_outputs = { };
	
	// Add output to logging in
	void SerialLog::addOutput(Stream *stream)
	{
		_outputs.push_back(stream);
	}

	// `printf` function 
	void SerialLog::_printf(const char* format, ...)
	{
		va_list arg;
		va_start(arg, format);
		char temp[64];
		char *buffer = temp;
		size_t len = vsnprintf(temp, sizeof(temp), format, arg);
		va_end(arg);
		if (len > sizeof(temp) - 1)
		{
			buffer = new char[len + 1];
			if (!buffer)
			{
				return;
			}
			va_start(arg, format);
			vsnprintf(buffer, len + 1, format, arg);
			va_end(arg);
		}

		for (Stream *s : SerialLog::_outputs) s->write(buffer);
	}
}

// Get filename
#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

// Levels
#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define INFO_LEVEL      0x02
#define DEBUG_LEVEL     0x03

// Set log level
#ifndef LOG_LEVEL
#define LOG_LEVEL   DEBUG_LEVEL
#endif


// Printing function
#define PRINTFUNCTION(format, ...)      dream::SerialLog::_printf(format, __VA_ARGS__)
// #define PRINTFUNCTION(format, ...)      fprintf(stderr, format, __VA_ARGS__)

// Log line template
#define LOG_FMT             " %s | %s:%d\t | %-12s | "
#define LOG_ARGS(LOG_TAG)   LOG_TAG, _FILE, __LINE__, __FUNCTION__

// Line ending
#define NEWLINE     "\n"

// Tag names
#define ERROR_TAG   "[E]"
#define INFO_TAG    "[I]"
#define DEBUG_TAG   "[D]"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG), ## args)
#else
#define LOG_DEBUG(message, args...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, args...)      PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG), ## args)
#else
#define LOG_INFO(message, args...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## args)
#else
#define LOG_ERROR(message, args...)
#endif

#if LOG_LEVEL >= NO_LOGS
#define LOG_IF_ERROR(condition, message, args...) if (condition) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## args)
#else
#define LOG_IF_ERROR(condition, message, args...)
#endif
