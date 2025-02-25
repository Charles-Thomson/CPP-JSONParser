#ifndef TYPE_CONVERSIONS_H
#define TYPE_CONVERSIONS_H

#include "../Structs/JSONValueStruct.h"

#include <vector>
#include <variant> 
#include <iostream>
#include <any>

using std::variant;
using std::cout;
using std::endl;
using std::vector;
using std::any;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer);

double GetDoubleFromJSONValue(const shared_ptr<JSONValue>& pointer);

bool GetBoolFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer);

any getCorrectTypeFromJSONValue(const shared_ptr<JSONValue>& pointer);

vector<string> stringToVector(const string& inputString);

vector<any> ConvertVectorStringToVectorAny(vector<string>& inputVector);
#endif // !TYPE_CONVERSIONS_H