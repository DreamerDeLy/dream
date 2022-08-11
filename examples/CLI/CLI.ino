
// Include library
#include <debug/cli.h>

// Create CLI object
dream::CommandLineInterface cli = dream::CommandLineInterface();

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Init CLI
	cli.init();

	// Add commands
	cli.addCommand({"on", "[pin] Set HIGH signal on pin", [](dream::CommandParams p){
		digitalWrite(p[0].toInt(), HIGH);
	}});
	cli.addCommand({"off", "[pin] Set LOW signal on pin", [](dream::CommandParams p){
		digitalWrite(p[0].toInt(), LOW);
	}});
}

void loop()
{
	// If there is available data
	if (Serial.available() > 0)
	{
		// Read data
		String input = Serial.readString();

		// Run command
		cli.run(input);
	}
}