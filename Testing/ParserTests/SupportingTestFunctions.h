#ifndef SUPPORTING_TEST_FUNCTIONS_H
#define SUPPORTING_TEST_FUNCTIONS_H

#include "../../HelperFunctions/TypeConversions.h"
#include "../../Structs/JSONValueStruct.h"

#include <variant>
#include <istream>

using std::variant;
using std::cout;
using std::endl;
using std::string;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONVector GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer);

vector<string> stringToVector(const string& inputString);

bool checkIfSearchKey(const string& searchKey, const string& key);

bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string& searchKey);

bool compareJSONValueToTestValue(shared_ptr<JSONValue>& pointerValue, any& anyValue);

#endif // !SUPPORTING_TEST_FUNCTIONS_H