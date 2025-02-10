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


tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const tuple<string, string, string, bool> rawTestData);

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData();


#endif TEST_DATA_PRE_PROCESSING_H