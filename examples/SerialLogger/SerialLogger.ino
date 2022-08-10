
#define LOG_LEVEL 3 // All
#include <debug/serial_logging.h>

void setup()
{
	Serial.begin(115200);
	dream::SerialLogging::addOutput(&Serial);

	LOG_DEBUG("Hello from SerialLogging!");

	LOG_INFO("It's number: %d", 69);

	LOG_ERROR("And it's an error(");

	LOG_IF_ERROR((6 == 7), "Oh, 6 != 7...");
}

void loop()
{
	delay(1000);
}