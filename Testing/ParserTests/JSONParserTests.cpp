#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 

#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"
#include "CPP-JSONParser.h"

using std::list;
using std::cout;
using std::endl;

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



TEST(JSONParserTests, ValidStringTest) {
	
	FileReader newFileReader("C:/Users/Charl/source/repos/C++/JSONParser/TestStrings/ValidString.txt");

	pair<string, bool> returnedData = newFileReader.GetFileContents();

	string data = returnedData.first;

	shared_ptr <JSONValue> ParsedData = ParseJson(data);

	for (string key : VALID_STRING_TEST_KEYS) {
		bool holder = CheckKeyExists(ParsedData, key);
		cout << holder << endl;
		ASSERT_TRUE(holder);

	};

	// The issue is due to the nested element containing a key that needs to be checked 
	// Need to write a func to reach into the nested elements 
	
}