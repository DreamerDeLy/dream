/*
================================================================================
 DREAM core / HTTP package generator
--------------------------------------------------------------------------------
 
 HTTP package generator. 
 Commands have to be called in right order as in examples.
 Commands can by layered (`p.setUserAgent("esp").setContentType("text/html");`).
 
--------------------------------------------------------------------------------
 Copyright © 2019-2023 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#pragma once

#include <Arduino.h>

#include <base64.h> // BasicAuth
#include "http_common.h"

namespace dream
{
	class HTTPRequest
	{
		protected: //-----------------------------------------------------------

		String _buffer = "";

		public: //--------------------------------------------------------------

		HTTPRequest(HTTPRequestType type, const String &host, const String &url)
		{
			_buffer += HTTPTypeToString(type) + " " + url + " HTTP/1.1\r\n";
			_buffer += "Host: " + host + "\r\n";
		}

		// Add custom header
		HTTPRequest& addHeader(const String &name, const String &value)
		{
			_buffer += (name + ": " + value + "\r\n");
			return *this;
		}

		// Set User-Agent header
		HTTPRequest& setUserAgent(const String &user_agent)
		{
			return addHeader(F("User-Agent"), user_agent);
		}

		// Set Content-Type header
		HTTPRequest& setContentType(const String &content_type)
		{
			return addHeader(F("Content-Type"), content_type);
		}

		// Set BasicAuth 
		HTTPRequest& setAuthorization(const String &user, const String &pass)
		{
			_buffer += "Authorization: Basic " + base64::encode(user + ":" + pass);
			return *this;
		}

		// Add package body
		HTTPRequest& setBody(const String &data)
		{
			addHeader(F("Content-Length"), String(data.length()));

			_buffer += "Connection: close\r\n\r\n";
			_buffer += data + "\r\n";

			return *this;
		}

		// End package
		HTTPRequest& setEmptyBody()
		{
			_buffer += "Connection: close\r\n\r\n";
			return *this;
		}

		// Get package
		String getBuffer()
		{
			return _buffer;
		}
	};
} 
