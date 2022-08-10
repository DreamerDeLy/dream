# DREAM

<p align="center">
  <img alt="logo" src="extra/logo.png">
</p>

DREAM (_**D**ynamic **R**eal-time **E**mbedded **A**rduino **M**odules_) is a collection of usefull modules for ESP8266/ESP32 projects on the Arduino Framework.

## Installation 

**For PlatformIO**: 

Just add following line to `platformio.ini` file of your project:

```ini
lib_deps = 
	https://github.com/DreamerDeLy/dream.git
```

**For ArduinoIDE**: 

1. Download source code as zip (green button "Code" > Download ZIP) or go to the Releases tab and download one of versions. 
2. Open the Arduino IDE and click to the "Sketch" menu and then Include Library > Add ZIP library.
3. Select downloaded ZIP file. 

## Build & testing

This project created with [PlatformIO](https://platformio.org/).

Use this command to build one of the examples: 

`pio ci --board=esp32dev examples/SerialLogger/ --lib src/`

Use this command to run tests (you have to have connected ESP32 to your computer):

`pio test`

## Modules

- **Containers**
  - **Value** - Container for any single value that stores the data type, units of measurement, the sensor from which the data was obtained, and a name.
  - **Data** - Container for a set of `Value` objects, which has tools for their search and processing, as well as the function of averaging data in an array of `Data` objects.
  - **Units Convert** - Tool for converting values from one units to other. 
- **Debug**
  - **CLI** - Library for the developer's CLI, into which any command can be integrated.
  - **Serial Logging** - Macro-based logging library.
- **Realtime**
  - **Simple Timer** - Simple software timer. 
  - **Simple Stopwatch** - A simple object for measuring the elapsed time between the execution of some functions. 

## License 

Copyright © 2019-2022 Dmytro Obukhov (DeLy Dreamer)

License: https://www.gnu.org/licenses/gpl-3.0.html