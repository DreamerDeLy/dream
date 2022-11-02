/*
================================================================================
 DREAM core / Command Line Interface
--------------------------------------------------------------------------------

 The CLI allows you to execute user commands typed into the terminal or sent.

--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>

#include <vector>
#include <functional>

namespace dream
{
	// Function parameters 
	typedef std::vector<String> CommandParams;

	// Command function
	typedef std::function<void(CommandParams)> CommandFunction;

	class CommandLineInterface
	{
		private: //-------------------------------------------------------------

		// Command struct
		struct Command
		{
			String name;
			String info;
			CommandFunction run;
		};

		// Available commands list
		std::vector<Command> _commands;

		// Source for continuous reading
		Stream *_source = nullptr;

		// Function to call in case of error
		std::function<void(String)> _errorHandler;

		// Get first substring by separator
		static String getFirstArgument(const String &data, const char separator)
		{
			String result = "";

			for(char c : data)
			{
				if (c != separator)
				{
					// Add to result
					result += c;
				}
				else
				{
					// Exit
					break;
				}
			}

			return result;
		}

		// Split string by separator
		static std::vector<String> splitString(const String &data, const char separator)
		{
			std::vector<String> result;
			String new_str = "";

			for (int i = 0; i < data.length(); i++)
			{
				char c = data[i];
				if (c != separator) 
				{
					new_str += c;
				}
				else
				{
					new_str.trim();
					if (!new_str.isEmpty()) result.push_back(new_str);
					new_str = "";
				}
			}

			if (!new_str.isEmpty()) result.push_back(new_str);

			return result;
		}

		public: //--------------------------------------------------------------

		// Init CLI in basic mode
		// In this mode you have to manually cal `run(string)` method.
		CommandLineInterface() { }

		// Init CLI with reading from source 
		// In this mode you have to place `tick()` method call to your `loop()` 
		// or you still can use `run(string)` method as well.
		CommandLineInterface(Stream *s) : _source(s) { }
		CommandLineInterface(Stream &s) : _source(&s) { }

		// Change mode to reading from source
		void setSource(Stream *s) { _source = s; }
		void setSource(Stream &s) { _source = &s; }

		// Set function to call in case of error
		// Error message will be set as String argument
		void onError(std::function<void(String)> f) { _errorHandler = f; }

		// Read commands from source 
		void tick()
		{
			// If source exist
			if (_source != nullptr)
			{
				if (_source->available() > 0)
				{
					// Read from source and run
					run(_source->readString());
				}
			}
		}

		// Add command to CLI
		void addCommand(Command cmd)
		{
			_commands.push_back(cmd);
		}

		// Get available commands
		std::vector<Command> getCommands()
		{
			return _commands;
		}

		// Run command from string
		void run(String command)
		{
			if (command.isEmpty()) return;

			// Trim string
			command.trim();

			// Parse command name and arguments
			const String name = getFirstArgument(command, ' ');
			const std::vector<String> params = splitString(command.substring(name.length()), ' ');

			// Find command
			for (const Command &c : _commands)
			{
				if (c.name == name)
				{
					// Run command
					c.run(params);

					return;
				}
			}
			
			// Command wasn't found
			_errorHandler("[CLI] Command " + command + " not found");
			return;
		}
	};
}
