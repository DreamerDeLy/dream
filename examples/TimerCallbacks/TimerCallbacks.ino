
// Include library
#include <realtime/simple_timer.h>

// Create timer and set interval
SimpleTimer timer = SimpleTimer(/* interval: */ 5000);

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Add callback
	timer.onElapsed(onTimer);

	// Set new interval
	timer.setInterval(1000);

	// Begin timer
	timer.begin();
}

void loop()
{
	// Check timer
	timer.tick();
}

void onTimer(SimpleTimer *t)
{
	// Reset timer
	t->reset();

	// Print message
	Serial.println("Timer triggered! " + String(millis()));
}