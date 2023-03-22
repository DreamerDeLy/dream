/*
================================================================================
 DREAM core / HTTP package generator
--------------------------------------------------------------------------------
 
 HTTP package generator. 
 Commands can by layered (`p.setUserAgent("esp").setContentType("text/html");`).
 
--------------------------------------------------------------------------------
 Copyright © 2019-2023 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>
#include <base64.h> // BasicAuth
#include <vector> // Headers list

#include "http_common.h"

namespace dream
{
	class HTTPRequest
	{
		private: //-------------------------------------------------------------

		HTTPMethod _type;
		String _host;
		String _url;

		// Package body
		String _body = "";

		// Package headers
		std::vector<HTTPHeader> _headers = { };

		// Check if header exist
		int findHeaderIndex(const String &name)
		{
			for (int i = 0; i < _headers.size(); i++)
			{
				if (_headers[i].name == name) return i;
			}
			
			return -1;
		};

		public: //--------------------------------------------------------------

		HTTPRequest(HTTPMethod type, const String &host, const String &url) :
			_type(type),
			_host(host),
			_url(url)
		{ }

		// Add custom header
		HTTPRequest& addHeader(const String &name, const String &value)
		{
			HTTPHeader header = { name, value };

			int i = findHeaderIndex(name);

			if (i != -1)
			{
				_headers[i] = header;
			}
			else
			{
				_headers.push_back(header);
			}

			// _buffer += (name + ": " + value + "\r\n");
			return *this;
		}

		// Set User-Agent header
		HTTPRequest& setUserAgent(const String &user_agent)
		{
			return addHeader("User-Agent", user_agent);
		}

		// Set Content-Type header
		HTTPRequest& setContentType(const String &content_type)
		{
			return addHeader("Content-Type", content_type);
		}

		// Set BasicAuth 
		HTTPRequest& setAuthorization(const String &user, const String &pass)
		{
			return addHeader("Authorization", "Basic " + base64::encode(user + ":" + pass));
		}

		// Add package body
		HTTPRequest& setBody(const String &data)
		{
			addHeader("Content-Length", String(data.length()));
	
			_body += data + "\r\n";

			return *this;
		}

		// Get package
		String toString()
		{
			String buffer = "";

			buffer += HTTPMethodToString(_type) + " " + _url + " HTTP/1.1\r\n";
			buffer += "Host: " + _host + "\r\n";

			for (const HTTPHeader &h : _headers)
			{
				buffer += h.name + ": " + h.value + "\r\n";
			}

			buffer += "Connection: close\r\n";

			if (_body.isEmpty() == false) 
			{
				buffer += "\r\n";
				buffer += _body;
			}

			return buffer;
		}
	};
} 
