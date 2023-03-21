#include <unity.h>

#include <net/http_request.h>

using namespace dream;

void setUp(void) 
{
	//
}

void tearDown(void) 
{
	//
}

void test_get(void)
{
	HTTPRequest get = HTTPRequest(GET, "google.com", "/")
		.setUserAgent("ESP")
		.addHeader("X-My-Header", "value");

	String package_have_to_be;
	package_have_to_be += "GET / HTTP/1.1\r\n";
	package_have_to_be += "Host: google.com\r\n";
	package_have_to_be += "User-Agent: ESP\r\n";
	package_have_to_be += "X-My-Header: value\r\n";
	package_have_to_be += "Connection: close\r\n";

	TEST_ASSERT_EQUAL_STRING(package_have_to_be.c_str(), get.toString().c_str());
}

void test_post(void)
{
	HTTPRequest post = HTTPRequest(POST, "eco-city.org.ua", "/input")
		.setUserAgent("ESP")
		.setContentType("application/json")
		.setAuthorization("qwerty", "123456")
		.setBody("{\"data\": true}");

	String package_have_to_be;
	package_have_to_be += "POST /input HTTP/1.1\r\n";
	package_have_to_be += "Host: eco-city.org.ua\r\n";
	package_have_to_be += "User-Agent: ESP\r\n";
	package_have_to_be += "Content-Type: application/json\r\n";
	package_have_to_be += "Authorization: Basic cXdlcnR5OjEyMzQ1Ng==\r\n";
	package_have_to_be += "Content-Length: 14\r\n";
	package_have_to_be += "Connection: close\r\n";
	package_have_to_be += "\r\n";
	package_have_to_be += "{\"data\": true}\r\n";

	TEST_ASSERT_EQUAL_STRING(package_have_to_be.c_str(), post.toString().c_str());
}

void test_various_order(void)
{
	HTTPRequest post = HTTPRequest(POST, "eco-city.org.ua", "/input")
		.setBody("{\"data\": true}")
		.setContentType("application/json")
		.setUserAgent("ESP")
		.setAuthorization("qwerty", "123456");

	String package_have_to_be;
	package_have_to_be += "POST /input HTTP/1.1\r\n";
	package_have_to_be += "Host: eco-city.org.ua\r\n";
	package_have_to_be += "Content-Length: 14\r\n";
	package_have_to_be += "Content-Type: application/json\r\n";
	package_have_to_be += "User-Agent: ESP\r\n";
	package_have_to_be += "Authorization: Basic cXdlcnR5OjEyMzQ1Ng==\r\n";
	package_have_to_be += "Connection: close\r\n";
	package_have_to_be += "\r\n";
	package_have_to_be += "{\"data\": true}\r\n";

	TEST_ASSERT_EQUAL_STRING(package_have_to_be.c_str(), post.toString().c_str());
}

void setup() 
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_get);
    RUN_TEST(test_post);
    RUN_TEST(test_various_order);

    UNITY_END();
}

void loop() 
{
	delay(1000);
}