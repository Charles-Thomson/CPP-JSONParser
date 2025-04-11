
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
using std::size_t;

//*
//  @brief Get Test Keys and Valeus for given test file
// 
//  Read thet Keys and Values test data values for a given test file, remove 
//  key idntifiers for Key and Value strings
// @ param string reference to testFileName var
// @ return tuple<string, string> testKeys and testValues strings 
// 
// */
tuple<string, string> GetTestFileKeysAndValues(string& testFileName) {
    string fullPath = string(TEST_FILE_PATH) + testFileName + "KeysAndValues.txt";

    ifstream inputfile(fullPath);
    string testKeysIdentifier = "#TEST_KEYS#";
    string testValuesIdentifier = "#TEST_VALUES#";

    if (!inputfile) {
        cerr << "Error Opening File : " << fullPath << endl;
    }

    string line;
    string testKeys;
    string testValues;
    string stringHolder;

    while (getline(inputfile, line)) {
        stringHolder = line;

        if (stringHolder.find(testKeysIdentifier) != string::npos) {
            testKeys += line;
        }
        else if (stringHolder.find(testValuesIdentifier) != string::npos) {
            testValues += line;
        }
    }

    size_t testKeysIdentifierPos = testKeys.find(testKeysIdentifier);
    size_t testValuesIdentifierPos = testValues.find(testValuesIdentifier);

    // Remove the Identifier tags from the strings - this needs to be tested 
    if (testKeysIdentifierPos != std::string::npos) {
        testKeys.erase(testKeysIdentifierPos, testKeysIdentifier.length());
    }

    if (testValuesIdentifierPos != std::string::npos) {
        testValues.erase(testValuesIdentifierPos, testValuesIdentifier.length());
    }
 
    return { testKeys, testValues };
}


//*
// @ Brief Process raw test data to usable format 
// 
//  Process the given raw test data into JSON, list of keys, list of stored Values
// 
// @param tuple<string, string, string, bool> rawTestData : strings of the raw data, bool idicates if test file read was sucessful
// @ return tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> : Formatted test data 
// */
tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const string testData, const tuple<string, string> keyAndValueData) {

	shared_ptr<JSONValue> JSONData = ParseToJSON(testData);

	vector<string> keyVector = stringToVector(get<0>(keyAndValueData));

	vector<string> valueVector = stringToVector(get<1>(keyAndValueData));

	return { JSONData, keyVector, valueVector };
}

//*
// @ brief Retrive and Format Test Data
// 
// Retrive raw test data and pass off for formatting to desiered type
// 
// @return tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> : Formated test data -> JSONData, list of Keys in JSON, list of values JSON
// */
tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData(string& testFileName) {
	FileReader newFileReader;

    string filePath = string(TEST_FILE_PATH) + testFileName + ".txt";

	string testData = newFileReader.GetFileContents(filePath);

    tuple<string, string> testKeysAndValues = GetTestFileKeysAndValues(testFileName);

	tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processedTestData = processTestData(testData, testKeysAndValues);

	return processedTestData;
}

//*
// @brief Read the Type test files
// 
// 
// @ param fileName the name of the test file
// */
shared_ptr<JSONValue> ReadAndParseTypeTestFile(string fileName) {
    FileReader newFileReader;

    string testData = newFileReader.GetFileContents(fileName);

    shared_ptr<JSONValue> parsedData = ParseToJSON(testData);

    return parsedData;
}