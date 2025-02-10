#ifndef TYPE_CONVERSIONS_H
#define TYPE_CONVERSIONS_H

#include "../Structs/JSONValueStruct.h"

#include <vector>
#include <variant> 
#include <iostream>

using std::variant;
using std::cout;
using std::endl;
using std::vector;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer);

vector<string> stringToVector(const string& inputString);
#endif // !TYPE_CONVERSIONS_H