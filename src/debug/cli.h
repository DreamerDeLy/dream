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
	typedef std::function<void(CommandParams params, Print& output)> CommandFunction;

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

		// Output for command result
		Print *_output = nullptr;

		// Function to call in case of error
		std::function<void(String)> _errorHandler;

		// Get first substring
		static String getFirstArgument(const String &data)
		{
			String result = "";

			for(char c : data)
			{
				if (c != ' ')
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
		static std::vector<String> splitString(const String &data)
		{
			std::vector<String> result;
			String new_str = ""; // Buffer for new argument 
			char current_quotation_marks = ' ';

			for (int i = 0; i < data.length(); i++)
			{
				char c = data[i];

				// Check string in
				if (current_quotation_marks == ' ')
				{
					if (c == '"' || c == '\'' )
					{
						current_quotation_marks = c;
						continue;
					}
				}
				else
				{
					if (c == current_quotation_marks)
					{
						current_quotation_marks = ' ';
						continue;
					}
				}

				if (c == ' ' && current_quotation_marks == ' ') 
				{
					new_str.trim();
					if (!new_str.isEmpty()) result.push_back(new_str);
					new_str = "";
				}
				else
				{
					new_str += c;
				}
			}

			if (!new_str.isEmpty()) result.push_back(new_str);

			return result;
		}

		// Run command
		void runCommand(String command, Print *output)
		{
			if (command.isEmpty()) 
			{
				_errorHandler("Command is empty");
				return;
			}

			if (output == nullptr)
			{
				_errorHandler("Output not specified");
				return;
			}

			// Trim string
			command.trim();

			// Parse command name and arguments
			const String name = getFirstArgument(command);
			const std::vector<String> params = splitString(command.substring(name.length()));

			// Find command
			for (const Command &c : _commands)
			{
				if (c.name == name)
				{
					// Run command
					c.run(params, *output);

					return;
				}
			}
			
			// Command wasn't found
			_errorHandler("Command " + command + " not found");
			return;
		}

		public: //--------------------------------------------------------------

		// Init CLI with default input and output
		CommandLineInterface() : _source(&Serial), _output(&Serial) { }

		// Init CLI with input and output specified
		CommandLineInterface(Stream *source, Print *output) : _source(source), _output(output) { }
		CommandLineInterface(Stream &source, Print &output) : _source(&source), _output(&output) { }

		// Change source
		void setSource(Stream *s) { _source = s; }
		void setSource(Stream &s) { _source = &s; }
		
		// Change source
		void setOutput(Print *s) { _output = s; }
		void setOutput(Print &s) { _output = &s; }

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
			runCommand(command, _output);
		}

		// Run command from string with separate output
		void run(String command, Print &output)
		{
			runCommand(command, &output);
		}

		// Run command from string with separate output
		void run(String command, Print *output)
		{
			runCommand(command, output);
		}
	};
}
