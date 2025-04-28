#include <gtest/gtest.h>
#include <fmt/core.h>

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


#include "../../FileReader/FileReader.h"
#include "../../Structs/JSONValueStruct.h"
#include "../../CPP-JSONParser.h"
#include "../../Testing/TestDataPreProcessing/TestDataPreProcessing.cpp"
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
using fmt::format;

vector<string> getTestFiles() {
	return {
		"ValidString",
		"ValidStringWhiteSpace",
		"ValidStringWithArray",
		"ValidMultiLine",
		"ValidStringWithDecimals"
	};
}
// Define a test classes that inherit from TestWithParam<int>
class TestKeyExists : public ::testing::TestWithParam<string> {};

class TestGetValueByKeyWithTemplateType : public ::testing::TestWithParam<string> {};

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

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);
	auto [JSONData, keyList, valuesList] = testData;

	for (string key : keyList) {
		bool holder = checkIfContainsKey(JSONData, key);
		SCOPED_TRACE(fmt::format("TestKeyExists-> The given key is not found : {} ", key));
		ASSERT_TRUE(holder);
	};
}


//*
// @ Brief Test GetValueByKeyWithT Function
// 
// Test if the function returns the correct value, in the correct type
// */
TEST_P(TestGetValueByKeyWithTemplateType, functionTest_GetValueByKeyWithT) {
	string testFileName = GetParam();

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);
	auto [JSONData, keyList, valuesList] = testData;

	vector<any> correctValuesList = ConvertVectorStringToVectorAny(valuesList);

	any expectedValue = correctValuesList[0];
	string returnedValue = GetValueByKeyWithType<string>(JSONData, keyList[0]);

	cout << "The Returned Value : " << returnedValue << endl;

	

}

//*
// @ brief Test if key,value pairs have been correctly parsed into JSON structure
// 
//  Test if the key,vakue opairs are present and of the expercted type following JSON parsing
// - retrieves test JSON data alogn side expected keys and values
// - compares each value returned by key ref from the JSON structure to the expected value/type
// */
TEST_P(TestValueAssignments, ValueAssignments) {
	// Get the test file names
	string testFileName = GetParam();

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData(testFileName);
	auto [JSONData, keyList, valuesList] = testData;

	vector<any> correctValuesList = ConvertVectorStringToVectorAny(valuesList);

	for (int i = 0; keyList.size() > i; i++) {
		any expectedValue = correctValuesList[i];

		shared_ptr<JSONValue> returnedValue = GetValueByKey(JSONData, keyList[i]);

		string valueType = returnedValue->getType();

		cout << "The type of the held value : " << valueType << endl;

		bool result = compareJSONValueToTestValue(returnedValue, expectedValue);

		SCOPED_TRACE(fmt::format("TestValueAssignment->the reuslt of comparison : {} ", result));
		SCOPED_TRACE(fmt::format("TestValueAssignment->Test File Name : {} ", testFileName));
		ASSERT_TRUE(result);
	}
}

INSTANTIATE_TEST_SUITE_P(JSONParserTestKeyExists, TestKeyExists,  ::testing::ValuesIn(
	getTestFiles()
));


INSTANTIATE_TEST_SUITE_P(JSONParserTestGetValueByKeyWithTemplateType, TestGetValueByKeyWithTemplateType, ::testing::ValuesIn(
	getTestFiles()
));

INSTANTIATE_TEST_SUITE_P(JSONParserTestValueAssignments, TestValueAssignments, ::testing::ValuesIn(
	getTestFiles()
));





