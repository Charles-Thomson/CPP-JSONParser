#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <fstream> 
#include <tuple>
#include <sstream>
#include <typeindex>
#include <variant>
#include <unordered_map>
#include <format>
#include <map>
#include <memory>
#include <cassert>

#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"
#include "CPP-JSONParser.h"
#include "Testing/TestDataPreProcessing/TestDataPreProcessing.cpp"
#include "SupportingTestFunctions.h"

using std::stringstream;
using std::list;
using std::cout;
using std::endl;
using std::getline;
using std::tuple;
using std::type_index;
using std::variant;
using std::min;
using std::visit;

vector<string> getTestFiles() {
	return {
		"ValidString",
		"ValidStringWhiteSpace",
		"ValidStringWithArray",
		"ValidMultiLine"
	};
}
// Define a test classes that inherit from TestWithParam<int>
class TestKeyExists : public ::testing::TestWithParam<string> {};

class TestGetValueByKey : public ::testing::TestWithParam<string> {};

class TestValueAssignments : public ::testing::TestWithParam<string> {};


//*
// @ brief Test if Key exists in JSON
// 
// Test if a given key ehas been correctly parsed to the JSON structure
// - Retrives test data containing a list of expected keys
// - Test each key to check it has been correctly parsed into the JSON structure
// 
// */
TEST_P(TestKeyExists, KeyExistsTest) {
	string testFileName = GetParam();
	cout << testFileName << endl;

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);
	auto [JSONData, keyList, valuesList] = testData;

	for (string key : keyList) {
		bool holder = checkIfContainsKey(JSONData, key);
		cout << "The result of the key check: " << key << " is " << holder << endl;
		ASSERT_TRUE(holder);
	};
}

//*
// @ brief Get a value by Key from JSON Structure
// 
// Test if a value can be retrieved for the JSON structure
// - Retrives test data containing a list of the expected stored keys and values
// - pulls from the JSON structure using given key
// - compares result to expected result
// 
// */
TEST_P(TestGetValueByKey, GetValueByKey) {
	string testFileName = GetParam();
	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);

	auto [JSONData, keyList, valuesList] = testData;

	string testKey = keyList[0];

	auto rerurnedValue = GetValueByKey(JSONData, testKey);
	auto result = getCorrectTypeFromJSONValue(rerurnedValue);

	any expectedValue = valuesList[0];

	string expectedValueAsString = std::any_cast<string>(expectedValue);
	string resultAsString = std::any_cast<string>(result);

	cout << "The expected Value : " << expectedValueAsString << " The returned value: " << resultAsString << endl;

	ASSERT_EQ(expectedValueAsString, resultAsString);
}

//*
// @ brief Test if key,value pairs have been correctly parsed into JSON structure
// 
//  Test if the key,vakue opairs are present and of the expercted type following JSON parsing
// - retrieves test JSON data alogn side expected keys and values
// - compares each value returned by key ref from the JSON structure to the expected value/type
// 
// */
TEST_P(TestValueAssignments, ValueAssignments) {

	string testFileName = GetParam();
	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);
	auto [JSONData, keyList, valuesList] = testData;

	vector<any> correctValuesList = ConvertVectorStringToVectorAny(valuesList);

	for (int i = 0; keyList.size() > i; i++) {
		string Key = keyList[i];
		any expectedValue = correctValuesList[i];

		// Get the stored value
		shared_ptr<JSONValue> rerurnedValue = GetValueByKey(JSONData, Key);

		bool result = compareJSONValueToTestValue(rerurnedValue, expectedValue);

		cout << "TestValueAssignment -> the reuslt of comparison : " << result << endl;

		ASSERT_TRUE(result);
	}
}

INSTANTIATE_TEST_SUITE_P(JSONParserTestKeyExists, TestKeyExists,  ::testing::ValuesIn(
	getTestFiles()
));

INSTANTIATE_TEST_SUITE_P(JSONParserTestGetValueByKey, TestGetValueByKey, ::testing::ValuesIn(
	getTestFiles()
));

INSTANTIATE_TEST_SUITE_P(JSONParserTestValueAssignments, TestValueAssignments, ::testing::ValuesIn(
	getTestFiles()
));





