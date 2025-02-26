
#include "TestDataPreProcessing.h"
#include "../../FileReader/FileReader.h"
#include "../../HelperFunctions/TypeConversions.h"
#include "../../Structs/JSONValueStruct.h"
#include "../../CPP-JSONParser.h"

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
using std::string;

//*
// @ Brief Process raw test data to usable format 
// 
//  Process the given raw test data into JSON, list of keys, list of stored Values
// 
// @param tuple<string, string, string, bool> rawTestData : strings of the raw data, bool idicates if test file read was sucessful
// @ return tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> : Formatted test data 
// */
tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const tuple<string, string, string, bool> rawTestData) {

	shared_ptr<JSONValue> JSONData = ParseToJSON(get<0>(rawTestData));

	vector<string> keyArray = stringToVector(get<1>(rawTestData));

	vector<string> valueTypeArray = stringToVector(get<2>(rawTestData));

	return { JSONData, keyArray, valueTypeArray };
}

//*
// @ brief Retrive and Format Test Data
// 
// Retrive raw test data and pass off for formatting to desiered type
// 
// @return tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> : Formated test data -> JSONData, list of Keys in JSON, list of values JSON
// */
tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData() {
	FileReader newFileReader;

	tuple<string, string, string, bool> rawTestData = newFileReader.GetFileContents("C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/ValidString.txt");

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processedTestData = processTestData(rawTestData);

	return processedTestData;
}