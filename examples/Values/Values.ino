
#include <containers/value.h>

using namespace dream;

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Create integer value [type, unit, sensor, value]
	Value v = Value("timespan", "s", "system", (millis() / 1000));

	// Create float value [type, unit, sensor, value, precision]
	// ! If you do not specify the precision, the value will be of the integer type
	Value temperature = Value("temperature", "C", "DHT11", 56.667f, 2);

	// Convert to string
	Serial.println("Value: " + v.toString());
	Serial.println("JSON: " + v.toJSON());
	Serial.println("As string: " + v.asString());

	// Check value
	Serial.println("Is null: " + String(v.isNull() ? "true" : "false"));
	Serial.println("Is number: " + String(v.isNumeric() ? "true" : "false"));

	// Change value
	v.setValue(v.asFloat() * 2.56f, 2);
	Serial.println("v * 2.56 = " + v.toString());
}

void loop()
{
	// Do nothing
	delay(1000);
}