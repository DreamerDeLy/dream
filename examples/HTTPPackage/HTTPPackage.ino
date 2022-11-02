
// Include library
#include <net/HTTPPackage.h>

using namespace dream;

const String user = "qwerty";
const String pass = "123456";

void setup()
{
	// Setup Serial port
	Serial.begin(115200);
	
	// Create GET request
	HTTPPackage get = HTTPPackage(HTTPRequestType::GET, "google.com", "/")
		.setUserAgent("ESP")
		.addHeader("X-My-Header", "value")
		.setEmptyBody();
	
	// Print package
	Serial.println(get.getBuffer());
	Serial.println();

	// Create POST request
	HTTPPackage post = HTTPPackage(HTTPRequestType::POST, "eco-city.org.ua", "/")
		.setUserAgent("ESP")
		.setContentType("application/json");

	// Set BasicAuth if credentials isn't empty
	if (user != "") post.setAuthorization(user, pass);

	// Set request body
	post.setBody("{\"data\": true}");

	// Print package
	Serial.println(post.getBuffer());
	Serial.println();
}

void loop()
{
	//
}
