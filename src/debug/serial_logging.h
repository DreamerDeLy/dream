/*
================================================================================
 DREAM core / SerialLogging module
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
#include <time.h>

namespace dream 
{
	class SerialLogging
	{
		private: //-------------------------------------------------------------

		static std::vector<Stream*> outputs;
		
		public: //--------------------------------------------------------------

		static void addOutput(Stream *stream);
		static inline char* timenow();
		static void printf(const char* format, ...);
	};

	std::vector<Stream*> SerialLogging::outputs = { };
			
	void SerialLogging::addOutput(Stream *stream)
	{
		outputs.push_back(stream);
	}

	inline char* SerialLogging::timenow()
	{
		static char buffer[64];
		time_t rawtime;
		struct tm *timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

		return buffer;
	}

	void SerialLogging::printf(const char* format, ...)
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

		for (Stream *s : SerialLogging::outputs) s->write(buffer);
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
#define PRINTFUNCTION(format, ...)      dream::SerialLogging::printf(format, __VA_ARGS__)
// #define PRINTFUNCTION(format, ...)      fprintf(stderr, format, __VA_ARGS__)

// Log line template
#define LOG_FMT             "%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)   dream::SerialLogging::timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

// Line ending
#define NEWLINE     "\n"

// Tag names
#define ERROR_TAG   "ERROR"
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

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
