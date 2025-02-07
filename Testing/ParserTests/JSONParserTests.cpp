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
#include "ExposedParserFunctions.cpp"



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


string getStringFromJSONValue(shared_ptr<JSONValue>& inputValue) {
	string data = get<string>(inputValue->value);

	return data;
}

vector<string> stringToVector(const string& inputString) {
	vector<string> stringList;
	stringstream ss(inputString);
	string word;

	while (getline(ss, word, ',')) {
		stringList.push_back(word);
	}
	return stringList;
}

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const tuple<string, string, string, bool> rawTestData) {

	shared_ptr<JSONValue> JSONData = ParseJson(get<0>(rawTestData));

	vector<string> keyArray = stringToVector(get<1>(rawTestData));

	vector<string> valueTypeArray = stringToVector(get<2>(rawTestData));

	return { JSONData, keyArray, valueTypeArray };
}

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData() {
	FileReader newFileReader;

	tuple<string, string, string, bool> rawTestData = newFileReader.GetFileContents("C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/ValidString.txt");

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processedTestData = processTestData(rawTestData);

	return processedTestData;
}








TEST(JSONParserTests, KeyExistsCheck) {

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();
	
	auto [JSONData, keyList, typleList] = testData;

	for (string key : keyList) {
		bool holder = checkIfContainsKey(JSONData, key);
		cout << "The result of the key check: " << key << " is " << holder << endl;
		ASSERT_TRUE(holder);	
	};	
}

using TypeVarient = variant<string, bool, int, double, JSONArray, JSONObject>;

unordered_map<string, type_index> typeMap = {
	{"string", typeid(string)},
	{"int", typeid(int)},
	{"double", typeid(double)},
	{"bool", typeid(bool)},
	{"JSONObject", typeid(JSONObject)},
	{"JSONArray", typeid(JSONArray)}
};

vector<type_index> stringVectorToTypesVector(vector<string>& stringList) {
	vector<type_index> typeList;


	for (const auto& typeName : stringList) {
		auto it = typeMap.find(typeName);

		if (it != typeMap.end()) {
			typeList.push_back(it->second);
		}
		else {
			cerr << "Unknown Type: " << typeName << endl;
		
		}
	}
	return typeList;

}

//using TypeVarient = variant<string, bool, double, JSONArray, JSONObject>;
//
//// Get the true type of the JSONValue
//TypeVarient JSONValueToTrueType(shared_ptr<JSONValue>& jv) {
//
//	if (holds_alternative<JSONArray>(jv->value)) {
//		return get<JSONArray>(jv->value);
//	}
//	else if (holds_alternative<JSONObject>(jv->value)) {
//		return get<JSONObject>(jv->value);
//	}
//	else if (holds_alternative<string>(jv->value)) {
//		return get<string>(jv->value);
//	}
//	else if (holds_alternative<double>(jv->value)) {
//		return get<double>(jv->value);
//	}
//	else if (holds_alternative<bool>(jv->value)) {
//		return get<bool>(jv->value);
//	}
//}

// Working on this test 
TEST(JSONParserTests, GetValueByKey) {
	string testKey = "name";

	// Gives the JSON, KeysList, TypesList
	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> testData = getTestData();

	auto [JSONData, keyList, stringTypleList] = testData;

	vector<type_index> trueTypeList = stringVectorToTypesVector(stringTypleList);


	int min_size = min(keyList.size(), trueTypeList.size());

	for (int i = 0; i < min_size; i++) {
		string key = keyList[i];

		shared_ptr<JSONValue> value = GetValueByKey(JSONData, key);

		/*auto trueValue = JSONValueToTrueValue(value);*/

		auto trueValue = "fail";
		if (holds_alternative<JSONArray>(value->value)) {
			auto trueValue = get<JSONArray>(value->value);
		}
		else if (holds_alternative<JSONObject>(value->value)) {
			auto trueValue = get<JSONObject>(value->value);
		}
		else if (holds_alternative<string>(value->value)) {
			auto trueValue = get<string>(value->value);
		}
		else if (holds_alternative<double>(value->value)) {
			auto trueValue = get<double>(value->value);
		}
		else if (holds_alternative<bool>(value->value)) {
			auto trueValue = get<bool>(value->value);
		}
		

		auto expectedType = trueTypeList[i];
		cout << "The true value type: " << typeid(trueValue).name() << "The expected Type: " << typeid(expectedType).name() << endl;	
	}

	ASSERT_EQ(1, 2);


}