#include <unity.h>

#include <containers/value.h>
#include <containers/units_convert.h>

using namespace dream;

void setUp(void) 
{
    // set stuff up here
}

void tearDown(void) 
{
    // clean stuff up here
}

void testToUGM3()
{
	Value ch2o = Value("ch2o", "ppb", "ZE08-CH2O", 15, 2);
	Value co2 = Value("co2", "ppm", "MH-Zx", 2200);
	Value no2 = Value("no2", "ppm", "MICS", 0.056, 6);
	Value co = Value("co", "ppm", "MICS", 0.67, 6);
	Value pm25 = Value("pm25", "ug/m3", "SDS011", 25.5, 1);

	TEST_ASSERT_EQUAL_FLOAT(18.421, UnitsConvert(&ch2o).toUGM3());
	TEST_ASSERT_EQUAL_FLOAT(3960020, UnitsConvert(&co2).toUGM3());
	TEST_ASSERT_EQUAL_FLOAT(105.381, UnitsConvert(&no2).toUGM3());
	TEST_ASSERT_EQUAL_FLOAT(767.558, UnitsConvert(&co).toUGM3());
	TEST_ASSERT_EQUAL_FLOAT(25.5, UnitsConvert(&pm25).toUGM3());
}

void testToPPB()
{
	Value ch2o = Value("ch2o", "ppb", "ZE08-CH2O", 15, 2);
	Value co2 = Value("co2", "ppm", "MH-Zx", 2200);
	Value no2 = Value("no2", "ppm", "MICS", 0.056, 6);
	Value co = Value("co", "ppm", "MICS", 0.67, 6);
	Value pm25 = Value("pm25", "ug/m3", "SDS011", 25.5, 1);

	TEST_ASSERT_EQUAL_FLOAT(15, UnitsConvert(&ch2o).toPPB());
	TEST_ASSERT_EQUAL_FLOAT(2200000, UnitsConvert(&co2).toPPB());
	TEST_ASSERT_EQUAL_FLOAT(56, UnitsConvert(&no2).toPPB());
	TEST_ASSERT_EQUAL_FLOAT(670, UnitsConvert(&co).toPPB());
	TEST_ASSERT_EQUAL_FLOAT(NULL_FLOAT, UnitsConvert(&pm25).toPPB());
}

void testToPPM()
{
	Value ch2o = Value("ch2o", "ppb", "ZE08-CH2O", 15, 2);
	Value co2 = Value("co2", "ppm", "MH-Zx", 2200);
	Value no2 = Value("no2", "ppm", "MICS", 0.056, 6);
	Value co = Value("co", "ppm", "MICS", 0.67, 6);
	Value pm25 = Value("pm25", "ug/m3", "SDS011", 25.5, 1);

	TEST_ASSERT_EQUAL_FLOAT(0.015, UnitsConvert(&ch2o).toPPM());
	TEST_ASSERT_EQUAL_FLOAT(2200, UnitsConvert(&co2).toPPM());
	TEST_ASSERT_EQUAL_FLOAT(0.056, UnitsConvert(&no2).toPPM());
	TEST_ASSERT_EQUAL_FLOAT(0.670, UnitsConvert(&co).toPPM());
	TEST_ASSERT_EQUAL_FLOAT(NULL_FLOAT, UnitsConvert(&pm25).toPPM());
}

void setup() 
{
	delay(2000);

    UNITY_BEGIN();

	RUN_TEST(testToUGM3);
	RUN_TEST(testToPPB);
	RUN_TEST(testToPPM);

    UNITY_END();
}

void loop() 
{
	delay(1000);
}