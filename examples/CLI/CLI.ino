
// Include library
#include <debug/cli.h>

// Create CLI object 
dream::CommandLineInterface cli = dream::CommandLineInterface();

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Add Serial as source and output for CLI
	cli.setSource(Serial);
	cli.setOutput(Serial);

	// Set function to call in case of error
	cli.onError([](String error_message){ 
		Serial.println("Error in CLI: " + error_message);
	});

	// Add commands
	cli.addCommand({"help", "Show available commands", [](dream::CommandParams p, Print &output){
		output.println("Available commands: ");
		for (auto c : cli.getCommands())
		{
			output.println(" - " + c.name + " " + c.info);
		}
	}});

	cli.addCommand({"on", "[pin] Set HIGH signal on pin", [](dream::CommandParams p, Print &output){
		// Get pin from parameters 
		int pin = p[0].toInt();
		
		// Set pin signal
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}});

	cli.addCommand({"off", "[pin] Set LOW signal on pin", [](dream::CommandParams p, Print &output){
		int pin = p[0].toInt();
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}});

	cli.addCommand({"read", "[pin] Read ADC on pin", [](dream::CommandParams p, Print &output){
		int pin = p[0].toInt();
		pinMode(pin, INPUT);
		
		// Print ADC value
		output.println("ADC: " + String(analogRead(pin)) + " on pin " + String(pin));
	}});
}

void loop()
{
	// Handle new commands from source
	cli.tick();
}