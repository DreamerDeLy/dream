
// Set log level to ALL 
// (Log level have to be set before including library)
#define LOG_LEVEL 3 

// Include library
#include <debug/serial_logging.h>

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Add Serial to logger outputs
	dream::SerialLog::setOutput(Serial);

	// Print to log
	LOG_DEBUG("Hello from SerialLogger!");

	// Print using formatting
	LOG_DEBUG("It's number: %d", 69);

	// Printing in other levels
	LOG_INFO("Interesting %s...", "thing");
	LOG_ERROR("And it's an error(");

	// Will be printed only if first argument is TRUE
	LOG_IF_ERROR((doSomething() == false), "Oh, no...");
}

void loop()
{
	// Do nothing
	delay(1000);
}

// Sample function
bool doSomething()
{
	return false;
}