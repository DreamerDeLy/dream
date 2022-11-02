
// Include library
#include <realtime/simple_timer.h>
using namespace dream;

// Create timer 
SimpleTimer timer = SimpleTimer();

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Begin timer
	timer.begin(/* interval: */ 5000);
}

void loop()
{
	if (timer.check())
	{
		// Reset timer
		timer.reset();

		// Print message
		Serial.println("Timer triggered! " + String(millis()));
	}
}
