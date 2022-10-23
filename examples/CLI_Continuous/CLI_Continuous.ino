
// Include library
#include <debug/cli.h>

// Create CLI object 
dream::CommandLineInterface cli = dream::CommandLineInterface();

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Add Serial as source for CLI
	cli.setSource(Serial);

	// Set function to call in case of error
	cli.onError([](String error_message){ 
		Serial.println("Error in CLI: " + error_message);
	});

	// Add commands
	cli.addCommand({"help", "Show available commands", [](dream::CommandParams p){
		Serial.println("Available commands: ");
		for (auto c : cli.getCommands())
		{
			Serial.println(" - " + c.name + " " + c.info);
		}
	}});

	cli.addCommand({"on", "[pin] Set HIGH signal on pin", [](dream::CommandParams p){
		// Get pin from parameters 
		int pin = p[0].toInt();
		
		// Set pin signal
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}});

	cli.addCommand({"off", "[pin] Set LOW signal on pin", [](dream::CommandParams p){
		int pin = p[0].toInt();
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}});
}

void loop()
{
	// Handle new commands from source
	cli.tick();
}