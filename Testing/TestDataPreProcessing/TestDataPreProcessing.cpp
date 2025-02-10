
#include "TestDataPreProcessing.h"
#include "HelperParserTestFunctions.h"

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

using std::tuple;

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