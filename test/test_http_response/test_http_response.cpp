#include <unity.h>

#include <net/http_response.h>

using namespace dream;

void setUp(void) 
{
	//
}

void tearDown(void) 
{
	//
}



void test_status(void)
{
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n\t\"key\": true\n}";

	auto parser = HTTPResponse(package);

	TEST_ASSERT_EQUAL_INT(200, parser.getStatus());
}

void test_headers_count(void)
{
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n\t\"key\": true\n}";

	auto parser = HTTPResponse(package);

	TEST_ASSERT_EQUAL_INT(8, parser.getHeaders().size());
}

void test_header_get(void)
{
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n\t\"key\": true\n}";

	auto parser = HTTPResponse(package);

	TEST_ASSERT_EQUAL_STRING("Tue, 14 Mar 2023 11:37:03 GMT", parser.getHeader("Date").c_str());
	TEST_ASSERT_EQUAL_STRING("Apache/2.4.38 (Debian)", parser.getHeader("Server").c_str());
	TEST_ASSERT_EQUAL_STRING("no-cache, must-revalidate", parser.getHeader("Cache-Control").c_str());
	TEST_ASSERT_EQUAL_STRING("application/json", parser.getHeader("Content-Type").c_str());
}

void test_body(void)
{
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n\t\"key\": true\n}";

	auto parser = HTTPResponse(package);

	TEST_ASSERT_EQUAL_STRING("{\n\t\"key\": true\n}", parser.getBody().c_str());
}

void test_values_headers(void)
{
	String package = "HTTP/1.1 200 OK\r\nDate: Tue, 14 Mar 2023 11:37:03 GMT\r\nServer: Apache/2.4.38 (Debian)\r\nCache-Control: no-cache, must-revalidate\r\nExpires: Sat, 26 Jul 1997 05:00:00 GMT\r\nVary: Accept-Encoding\r\nContent-Length: 19\r\nConnection: close\r\nContent-Type: application/json\r\n\r\n{\n    \"key\": true\n}";

	auto parser = HTTPResponse(package);

	TEST_ASSERT_EQUAL_STRING("application/json", parser.getContentType().c_str());
	TEST_ASSERT_EQUAL_STRING("Tue, 14 Mar 2023 11:37:03 GMT", parser.getDate().c_str());
	TEST_ASSERT_EQUAL_STRING("", parser.getLocation().c_str());
	TEST_ASSERT_EQUAL_INT(19, parser.getContentLength());
}

void setup() 
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_status);
    RUN_TEST(test_headers_count);
    RUN_TEST(test_header_get);
    RUN_TEST(test_body);
    RUN_TEST(test_values_headers);

    UNITY_END();
}

void loop() 
{
	delay(1000);
}