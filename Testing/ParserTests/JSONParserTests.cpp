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



TEST(JSONParserTests, GetValueByKey) {

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();

	auto [JSONData, keyList, valuesList] = testData;

	string testKey = keyList[0];

	auto returnedValue = GetValueByKey(JSONData, testKey);

	string value = GetStringFromJSONValue(returnedValue);

	cout << "The key used: " << testKey << " The reutrned value: " << value << endl;

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
