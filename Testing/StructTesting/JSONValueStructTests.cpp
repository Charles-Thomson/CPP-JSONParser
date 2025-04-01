

#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <variant>
#include "../../Structs/JSONValueStruct.h"

using std::cout;
using std::endl;
using std::variant;
using std::make_shared;
using std::string;

//*
// @ brief Compare two given string for equality
// 
// Compare two string representations of types. If the comparison fails, 
// provide given SCOPED_TRACE message
// 
// @param scopedTraceMesasge message provided to SCOPED_TRACE, displayed of comparison failure
// @param expected expected type - string representation
// @param actual actual type - string representation
// */
void typeComparisonHelper(const string& scopedTraceMesasge, const string& expected, const string& actual) {
	SCOPED_TRACE(scopedTraceMesasge);
	EXPECT_EQ(expected, actual);
}


TEST(JSONStructTest, GetValueFromJSONValueStruct) {
	double testDouble = 22.2;
	string testString = "22.2";
	bool testBool = false;
	JSONObject testJSONObject = JSONObject();;
	JSONArray testJSONArray = JSONArray();

	shared_ptr<JSONValue> testPointer_double = make_shared<JSONValue>(testDouble);
	shared_ptr<JSONValue> testPointer_string = make_shared<JSONValue>(testString);
	shared_ptr<JSONValue> testPointer_bool = make_shared<JSONValue>(testBool);
	shared_ptr<JSONValue> testPointer_JSONObject = make_shared<JSONValue>(testJSONObject);
	shared_ptr<JSONValue> testPointer_JSONArray = make_shared<JSONValue>(testJSONArray);

	typeComparisonHelper(
		"Returned value from shared_ptr<JSONValue>->getV<double>() returned an incorrect type",
		typeid(double).name(),
		typeid(testPointer_double->getV<double>()).name()
	);

	typeComparisonHelper(
		"Returned value from shared_ptr<JSONValue>->getV<string>() returned an incorrect type",
		typeid(string).name(),
		typeid(get<string>(testPointer_string->value)).name()
	);

	typeComparisonHelper(
		"Returned value from shared_ptr<JSONValue>->getV<bool>() returned an incorrect type",
		typeid(bool).name(),
		typeid(testPointer_bool->getV<bool>()).name()
	);

	typeComparisonHelper(
		"Returned value from shared_ptr<JSONValue>->getV<JSONObject>() returned an incorrect type",
		typeid(JSONObject).name(),
		typeid(testPointer_JSONObject->getV<JSONObject>()).name()
	);

	typeComparisonHelper(
		"Returned value from shared_ptr<JSONValue>->getV<JSONArray>() returned an incorrect type",
		typeid(JSONArray).name(),
		typeid(testPointer_JSONArray->getV<JSONArray>()).name()
	);	
}

