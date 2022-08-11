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
#include <functional>

#include "serial_logging.h"

namespace dream
{
	typedef std::vector<String> CommandParams;
	typedef std::function<void(CommandParams)> CommandFunction;

	class CommandLineInterface
	{
		private: //-------------------------------------------------------------

		struct Command
		{
			String name;
			String info;
			CommandFunction run;
		};

		std::vector<Command> commands;

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

		void command_help(CommandParams params)
		{
			LOG_DEBUG("Available commands:");
			for (const Command &c : commands)
			{
				LOG_DEBUG(" - %s %s", c.name.c_str(), c.info.c_str());
			}
		}

		public: //--------------------------------------------------------------

		CommandLineInterface() { }

		// Init CLI
		void init()
		{
			commands.push_back({"help", "Print info about CLI commands.", std::bind(&CommandLineInterface::command_help, this, std::placeholders::_1)});
		}

		// Add command to CLI
		void addCommand(Command cmd)
		{
			commands.push_back(cmd);
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
			for (const Command &c : commands)
			{
				if (c.name == name)
				{
					// Run command
					LOG_INFO("[CLI] Run command \"%s\"", command.c_str());
					c.run(params);

					return;
				}
			}
			
			// Command wasn't found
			LOG_INFO("[CLI] Command \"%s\" not found", command.c_str());
			return;
		}
	};
}
