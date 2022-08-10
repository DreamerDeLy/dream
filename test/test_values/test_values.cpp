#include <unity.h>

#include <containers/data.h>
#include <containers/data.cpp>

using namespace dream;

void setUp(void) 
{
	//
}

void tearDown(void) 
{
	//
}

void test_data_types(void)
{
	Data data = Data();

	data.addValue(Value("temperature", "C", "BME280", 30.50, 2));
	data.addValue(Value("humidity", "Rh", "BME280", 50.50, 2));
	data.addValue(Value("co2", "ppm", "MH-Zx", 865));
	data.addValue(Value("datetime", "", "system", "2022-08-02 15:30:05"));

	TEST_ASSERT_TRUE(data.values[0].data_type == ValueDataType::Float);
	TEST_ASSERT_TRUE(data.values[1].data_type == ValueDataType::Float);
	TEST_ASSERT_TRUE(data.values[2].data_type == ValueDataType::Int);
	TEST_ASSERT_TRUE(data.values[3].data_type == ValueDataType::String);
}

void test_data_strings(void)
{
	Data data = Data();

	data.addValues({
		Value("temperature", "C", "BME280", 30.50, 2),
		Value("humidity", "Rh", "BME280", 51.00, 2),
		Value("pressure", "Pa", "BME280", 99000.00, 2) });

	TEST_ASSERT_EQUAL_STRING("30.50", data.values[0].asString().c_str());
	TEST_ASSERT_EQUAL_STRING("51.00", data.values[1].asString().c_str());
	TEST_ASSERT_EQUAL_STRING("99000.00", data.values[2].asString().c_str());
}

void test_value_to_json(void)
{
	Data data = Data();

	data.addValues({
		Value("temperature", "C", "BME280", 30.50, 2),
		Value("humidity", "Rh", "BME280", 51.00, 2),
		Value("pressure", "Pa", "BME280", 99000.00, 2) });
	
	TEST_ASSERT_EQUAL_STRING("{\"type\":\"temperature\",\"unit\":\"C\",\"sensor\":\"BME280\",\"value\":\"30.50\"},", data.values[0].toJSON().c_str());
	TEST_ASSERT_EQUAL_STRING("{\"type\":\"humidity\",\"unit\":\"Rh\",\"sensor\":\"BME280\",\"value\":\"51.00\"},", data.values[1].toJSON().c_str());
	TEST_ASSERT_EQUAL_STRING("{\"type\":\"pressure\",\"unit\":\"Pa\",\"sensor\":\"BME280\",\"value\":\"99000.00\"},", data.values[2].toJSON().c_str());
}

void test_function_data_as(void) 
{
	Data data = Data();

	data.addValues({
		Value("temperature", "C", "BME280", 30.50, 2),
		Value("humidity", "Rh", "BME280", 51.00, 2),
		Value("pressure", "Pa", "BME280", 99000.00, 2) });

    TEST_ASSERT_EQUAL_FLOAT(30.5, data.values[0].asFloat());
    TEST_ASSERT_EQUAL_FLOAT(51.0, data.values[1].asFloat());
    TEST_ASSERT_EQUAL_FLOAT(99000.00, data.values[2].asFloat());
}

void test_avg(void)
{
	std::vector<Data> data_arr;

	Data data = Data();

	data.addValues({
		Value("temperature", "C", "BME280", 30.50, 2),
		Value("humidity", "Rh", "BME280", 50.50, 2),
		Value("pressure", "Pa", "BME280", 98000.00, 2) });

	data_arr.push_back(data);

	data.addValues({
		Value("temperature", "C", "BME280", NULL_FLOAT, 2),
		Value("humidity", "Rh", "BME280", NULL_FLOAT, 2),
		Value("pressure", "Pa", "BME280", NULL_FLOAT, 2) });

	data_arr.push_back(data);

	data.addValues({
		Value("temperature", "C", "BME280", NULL_FLOAT, 2),
		Value("humidity", "Rh", "BME280", NULL_FLOAT, 2),
		Value("pressure", "Pa", "BME280", NULL_FLOAT, 2) });

	data_arr.push_back(data);

	data.addValues({
		Value("temperature", "C", "BME280", 25.00, 2),
		Value("humidity", "Rh", "BME280", 51.00, 2),
		Value("pressure", "Pa", "BME280", 99000.00, 2) });

	data_arr.push_back(data);

	data.addValues({
		Value("temperature", "C", "BME280", NULL_FLOAT, 2),
		Value("humidity", "Rh", "BME280", NULL_FLOAT, 2),
		Value("pressure", "Pa", "BME280", NULL_FLOAT, 2) });

	data_arr.push_back(data);

	Data data_to_send = Data::calculateAvg(data_arr);
	TEST_ASSERT_EQUAL_FLOAT(27.75, data_to_send.values[0].asFloat());
    TEST_ASSERT_EQUAL_FLOAT(50.75, data_to_send.values[1].asFloat());
    TEST_ASSERT_EQUAL_FLOAT(98500, data_to_send.values[2].asFloat());
}

void setup() 
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_data_types);
    RUN_TEST(test_data_strings);
    RUN_TEST(test_value_to_json);
    RUN_TEST(test_function_data_as);
    RUN_TEST(test_avg);

    UNITY_END();
}

void loop() 
{
	delay(1000);
}