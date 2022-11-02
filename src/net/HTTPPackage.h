/*
================================================================================
 DREAM core / HTTP package generator
--------------------------------------------------------------------------------
 
 HTTP package generator. 
 Commands have to be called in right order as in examples.
 Commands can by layered (`p.setUserAgent("esp").setContentType("text/html");`).
 
--------------------------------------------------------------------------------
 Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)
 License: https://www.gnu.org/licenses/gpl-3.0.html
================================================================================
*/

#include <Arduino.h>

#include <base64.h> // BasicAuth

namespace dream
{
	enum class HTTPRequestType 
	{ 
		GET,
		POST,
		PUT
	};

	class HTTPPackage
	{
		protected: //-----------------------------------------------------------

		String _buffer = "";

		String typeToString(HTTPRequestType t)
		{
			switch (t)
			{
			case HTTPRequestType::GET: return "GET";
			case HTTPRequestType::POST: return "POST";
			case HTTPRequestType::PUT: return "PUT";
			}

			return "";
		}

		public: //--------------------------------------------------------------

		HTTPPackage(HTTPRequestType type, const String &host, const String &url)
		{
			_buffer += typeToString(type) + " " + url + " HTTP/1.1\r\n";
			_buffer += "Host: " + host + "\r\n";
		}

		// Add custom header
		HTTPPackage& addHeader(const String &name, const String &value)
		{
			_buffer += (name + ": " + value + "\r\n");
			return *this;
		}

		// Set User-Agent header
		HTTPPackage& setUserAgent(const String &user_agent)
		{
			return addHeader(F("User-Agent"), user_agent);
		}

		// Set Content-Type header
		HTTPPackage& setContentType(const String &content_type)
		{
			return addHeader(F("Content-Type"), content_type);
		}

		// Set BasicAuth 
		HTTPPackage& setAuthorization(const String &user, const String &pass)
		{
			_buffer += "Authorization: Basic " + base64::encode(user + ":" + pass);
			return *this;
		}

		// Add package body
		HTTPPackage& setBody(const String &data)
		{
			addHeader(F("Content-Length"), String(data.length()));

			_buffer += "Connection: close\r\n\r\n";
			_buffer += data + "\r\n";

			return *this;
		}

		// End package
		HTTPPackage& setEmptyBody()
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
