#ifndef TEST_DATA_PRE_PROCESSING_H
#define TEST_DATA_PRE_PROCESSING_H

#include "../../FileReader/FileReader.h"
#include "../../HelperFunctions/TypeConversions.h"
#include "../../Structs/JSONValueStruct.h"

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
using std::vector;
using std::string;

tuple<string, string> GetTestFileKeysAndValues(string& testFileName);

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const string testData, const tuple<string, string> keyAndValueData);

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData(string& filePath);


#endif TEST_DATA_PRE_PROCESSING_H