/*
================================================================================
 DREAM core / HTTP package parser
--------------------------------------------------------------------------------
 
 Class for parsing HTTP responses from server.
 Parser gets all data from string of HTTP package.
 
--------------------------------------------------------------------------------
 Copyright © 2019-2023 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>
#include <vector>

namespace dream
{
	class HTTPPackageParser
	{
		private: //-------------------------------------------------------------

		struct HTTPRequestHeader
		{
			String name;
			String value;
		};

		// Buffer for package as string
		String _buffer;

		// HTTP response code 
		int _http_code;

		// Headers
		std::vector<HTTPRequestHeader> _headers;

		int _content_length;
		String _content_type;
		String _location;
		String _date;

		// Body content
		String _body;

		// Parse package status code, headers and body
		void parse()
		{
			bool first_line = true;
			bool reading_body = false;

			String current_line = "";

			for (int i = 0; i < _buffer.length(); i++)
			{
				// Get current char
				char c = _buffer[i];

				if (reading_body)
				{
					// Add to the body 
					_body += c;
				}
				else
				{
					// Add to the buffer line
					current_line += c;

					if (c == '\n')
					{
						if (first_line)
						{
							// Parse response code
							int code_pos = _buffer.indexOf(' ') + 1;
							_http_code = _buffer.substring(code_pos, _buffer.indexOf(' ', code_pos)).toInt();

							first_line = false;
						}
						else
						{
							// If separation line
							if (current_line == "\r\n" || current_line == "\n")
							{
								reading_body = true;
							}
							else
							{
								// Parse header
								String name = current_line.substring(0, current_line.indexOf(':'));
								String value = current_line.substring(current_line.indexOf(':') + 1);
								value.trim();

								_headers.push_back({ name, value });
							}
						}

						// Reset current line
						current_line = "";
					}
				}
			}

			_body.trim();
		}
		
		// Fill fields from headers
		void headersDataToValues()
		{
			for (const auto &h : _headers)
			{
				if (h.name.equalsIgnoreCase("Content-Length"))
				{
					_content_length = h.value.toInt();
				}
				else if (h.name.equalsIgnoreCase("Date"))
				{
					_date = h.value;
				}
				else if (h.name.equalsIgnoreCase("Content-Type"))
				{
					_content_type = h.value;
				}
				else if (h.name.equalsIgnoreCase("Location"))
				{
					_location = h.value;
				}
			}
		}

		public: //--------------------------------------------------------------

		HTTPPackageParser(const String &package) 
		{
			_buffer = package;
			_buffer.trim();

			parse();
			headersDataToValues();
		}

		int getStatus() { return _http_code; }
		int getContentLength() { return _content_length; } 
		String getContentType() { return _content_type; } 
		String getLocation() { return _location; } 
		String getDate() { return _date; } 

		std::vector<HTTPRequestHeader> getHeaders()
		{
			return _headers;
		}

		bool hasHeader(const String &name)
		{
			for (const HTTPRequestHeader &h : _headers)
			{
				if (h.name == name) return true;
			}

			return false;
		}

		String getHeader(const String &name)
		{
			for (const HTTPRequestHeader &h : _headers)
			{
				if (h.name == name) return h.value;
			}

			return "";
		}

		String getBody()
		{
			return _body;
		}
	};
}