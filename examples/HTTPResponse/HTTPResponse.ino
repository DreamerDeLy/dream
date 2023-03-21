
// Include library
#include <net/http_response.h>

using namespace dream;

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Package string
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n    \"key\": true\n}";

	// Parse package
	HTTPResponse parser = HTTPResponse(package);

	// Print general values
	Serial.println("HTTP status: " + String(parser.getStatus()));
	Serial.println();
	Serial.println("Content length: " + parser.getContentType());
	Serial.println("Content type: " + parser.getContentType());
	Serial.println();

	// Print headers
	Serial.println("Headers: ");
	for (const auto &h : parser.getHeaders())
	{
		Serial.println(" - " + h.name + " = " + h.value);
	}
	Serial.println();

	// Print body
	Serial.println("Body: ");
	Serial.println(parser.getBody());
}

void loop()
{

}