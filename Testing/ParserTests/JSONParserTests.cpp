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



// Maybe change the incoming list to the ptr type ?
// seperate method for the comparison ? chack if each can be converted to the corecttype ?


// Values list has all its elements saved as string <- issue ?
TEST(JSONParserTests, TestValueAssignments) {
	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();

	auto [JSONData, keyList, valuesList] = testData;

	vector<any> correctValuesList = ConvertVectorStringToVectorAny(valuesList);

	//string testKey = keyList[2];

	//// Get Value
	//shared_ptr<JSONValue> rerurnedValue = GetValueByKey(JSONData, testKey);


	//// These are all of type string 
	//any expectedValue = correctValuesList[2];

	//
	//bool result1 = FinalCompareJSONValueToTestValue(rerurnedValue, expectedValue);

	cout << keyList.size() << endl;

	cout << correctValuesList.size() << endl;
	for (int i = 0; keyList.size() > i; i++) {

		string Key = keyList[i];
		any expectedValue = correctValuesList[i];
		
		// Get the stored value
		shared_ptr<JSONValue> rerurnedValue = GetValueByKey(JSONData, Key);

		bool result1 = FinalCompareJSONValueToTestValue(rerurnedValue, expectedValue);

		cout << "TestValueAssignment -> the reuslt of comparison : " << result1 << endl;
	}
	ASSERT_EQ(1, 2);
	
}


// Working on this test - does not function as expected need to test one function at a time
//TEST(JSONParserTests, GetValueByKey) {
//	string testKey = "name";
//
//	// Gives the JSON, KeysList, TypesList
//	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();
//
//	auto [JSONData, keyList, stringTypleList] = testData;
//
//	vector<type_index> trueTypeList = stringVectorToTypesVector(stringTypleList);
//
//
//	int min_size = min(keyList.size(), trueTypeList.size());
//
//	for (int i = 0; i < min_size; i++) {
//		string key = keyList[i];
//
//		shared_ptr<JSONValue> value = GetValueByKey(JSONData, key);
//
//		/*auto trueValue = JSONValueToTrueValue(value);*/
//
//		auto trueValue = "fail";
//		if (holds_alternative<JSONArray>(value->value)) {
//			auto trueValue = get<JSONArray>(value->value);
//		}
//		else if (holds_alternative<JSONObject>(value->value)) {
//			auto trueValue = get<JSONObject>(value->value);
//		}
//		else if (holds_alternative<string>(value->value)) {
//			auto trueValue = get<string>(value->value);
//		}
//		else if (holds_alternative<double>(value->value)) {
//			auto trueValue = get<double>(value->value);
//		}
//		else if (holds_alternative<bool>(value->value)) {
//			auto trueValue = get<bool>(value->value);
//		}
//		
//
//		auto expectedType = trueTypeList[i];
//		cout << "The true value type: " << typeid(trueValue).name() << "The expected Type: " << typeid(expectedType).name() << endl;	
//	}
//
//	ASSERT_EQ(1, 2);
//
//
//}
