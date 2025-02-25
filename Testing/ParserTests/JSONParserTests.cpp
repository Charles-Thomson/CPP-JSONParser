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

list<string> TEST_DATA_FILE_PATHS = {
	"ValidStringWhiteSpace.txt",
	"ValidString.txt",
	"ValidStringWithArray.txt"
};


TEST(JSONParserTests, KeyExistsCheck) {

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();
	
	auto [JSONData, keyList, typleList] = testData;

	for (string key : keyList) {
		bool holder = checkIfContainsKey(JSONData, key);
		cout << "The result of the key check: " << key << " is " << holder << endl;
		ASSERT_TRUE(holder);	
	};	
}

using std::variant;

TEST(JSONParserTests, GetValueByKey) {

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();

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



TEST(JSONParserTests, TestValueAssignments) {
	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();

	auto [JSONData, keyList, valuesList] = testData;

	vector<any> correctValuesList = ConvertVectorStringToVectorAny(valuesList);

	cout << keyList.size() << endl;

	cout << correctValuesList.size() << endl;
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



