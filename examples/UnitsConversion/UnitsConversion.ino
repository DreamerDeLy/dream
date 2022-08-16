
#include <containers/value.h>
#include <containers/units_convert.h>

using namespace dream;

void setup()
{
	// Setup Serial port
	Serial.begin(115200);

	// Create Value (NO₂ from MICS-6814 sensor in PPM)
	Value v = Value("no2", "ppm", "MICS-6814", 0.057789, 6);

	// Print original value
	Serial.println("Value: " + v.asString() + " " + v.unit);

	// Conversion
	Serial.println("   PPM = " + String(UnitsConvert(&v).toPPM()));
	Serial.println("   PPB = " + String(UnitsConvert(&v).toPPM()));
	Serial.println(" mg/m³ = " + String(UnitsConvert(&v).toPPM()));
	Serial.println(" µg/m³ = " + String(UnitsConvert(&v).toPPM()));
}

void loop()
{
	// Do nothing
	delay(1000);
}