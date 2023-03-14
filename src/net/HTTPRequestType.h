
#pragma once

#include <Arduino.h>

namespace dream
{
	enum class HTTPRequestType 
	{ 
		GET,
		POST,
		PUT
	};

	String HTTPTypeToString(HTTPRequestType t)
	{
		switch (t)
		{
		case HTTPRequestType::GET: return "GET";
		case HTTPRequestType::POST: return "POST";
		case HTTPRequestType::PUT: return "PUT";
		}

		return "";
	}
}