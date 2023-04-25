
#pragma once

#include <Arduino.h>

namespace dream
{
	enum HTTPMethod 
	{ 
		GET,
		POST,
		PUT
	};

	String HTTPMethodToString(HTTPMethod t);

	String HTTPMethodToString(HTTPMethod t)
	{
		switch (t)
		{
		case HTTPMethod::GET: return "GET";
		case HTTPMethod::POST: return "POST";
		case HTTPMethod::PUT: return "PUT";
		}

		return "";
	}

	// Object of HTTP package header
	struct HTTPHeader
	{
		String name;
		String value;

		String toString() const 
		{
			return String(name + ": " + value);
		}
	};
}