#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 
#include <tuple>

#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"
#include "CPP-JSONParser.h"
#include "ExposedParserFunctions.cpp"

#include <iostream>
#include <sstream>

using std::stringstream;
using std::list;
using std::cout;
using std::endl;
using std::getline;
using std::tuple;

list<string> TEST_DATA_FILE_PATHS = {
	"ValidStringWhiteSpace.txt",
	"ValidString.txt",
	"ValidStringWithArray.txt"
};

list<string> VALID_STRING_TEST_KEYS = {
	"name",
	"age",
	"address",
	"street"
};

list<string> stringToList(const string& inputString) const {
	list<string> stringList;
	stringstream ss(inputString);
	string word;

	while (getline(ss, word, ',')) {
		stringList.push_back(word);
	}
	return stringList;
}

tuple<shared_ptr<JSONValue>, list<string>, list<string>> processTestData(const tuple<string, string, string, bool> rawTestData) {

	shared_ptr<JSONValue> JSONData = ParseJson(get<0>(rawTestData));

	list<string> keyArray = stringToList(get<1>(rawTestData));

	list<string> valueTypeArray = stringToList(get<2>(rawTestData));

	return { JSONData, keyArray, valueTypeArray };
}

tuple<shared_ptr<JSONValue>, list<string>, list<string>> getTestData() {
	FileReader newFileReader;

	tuple<string, string, string, bool> rawTestData = newFileReader.GetFileContents("C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/ValidString.txt");

	tuple<shared_ptr<JSONValue>, list<string>, list<string>> processedTestData = processTestData(rawTestData);

	return processedTestData;
}




TEST(JSONParserTests, ValidStringTest) {
	
	FileReader newFileReader;

	tuple<string,string, bool> returnedData = newFileReader.GetFileContents("C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/ValidString.txt");
	
	string JSONTestString = get<0>(returnedData);

	cout << JSONTestString << endl;

	list<string> keyArray = keyStringToList(get<1>(returnedData));

	shared_ptr<JSONValue> ParsedData = ParseJson(JSONTestString);

	for (string key : keyArray) {
		bool holder = checkIfContainsKey(ParsedData, key);
		cout << "The result of the key check: " << key << " is " << holder << endl;
		ASSERT_TRUE(holder);
		
	};	
}

string getStringFromJSONValue(shared_ptr<JSONValue>& inputValue) {
	string data = get<string>(inputValue->value);

	return data; 
}


// Working on this test 
TEST(JSONParserTests, GetValueByKey) {
	string testKey = "name";

	tuple<shared_ptr<JSONValue>,list<string>, list<string>> testData = getTestData();

	
	for (string key : get<1>(testData)) {
		
	}



	shared_ptr<JSONValue> data = GetValueByKey(JSONTestData, testKey);

	string value = getStringFromJSONValue(data);

	cout << "The returned value is: " << value << endl;


}