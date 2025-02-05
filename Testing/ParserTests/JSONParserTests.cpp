#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 

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

list<string> keyStringToList(string& keyString) {
	list<string> keyArray;
	stringstream ss(keyString);
	string word;

	while(getline(ss, word, ',')) {
		keyArray.push_back(word);
	}
	return keyArray;
}


TEST(JSONParserTests, ValidStringTest) {
	
	FileReader newFileReader("C:/Users/Charl/source/repos/C++/JSONParser/TestStrings/ValidString.txt");

	tuple<string,string, bool> returnedData = newFileReader.GetFileContents();

	string JSONTestString = get<0>(returnedData);

	cout << JSONTestString << endl;

	list<string> keyArray = keyStringToList(get<1>(returnedData));

	shared_ptr <JSONValue> ParsedData = ParseJson(JSONTestString);

	for (string key : keyArray) {
		bool holder = checkIfContainsKey(ParsedData, key);
		cout << "The result of the key check: " << key << " is " << holder << endl;
		ASSERT_TRUE(holder);
	};	
}