#include<iostream>
#include<variant>
#include<String>
#include<unordered_map>
#include<vector>
#include<memory>

#include "JSONValueStruct.h"

using std::string;
using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::variant;
using std::nullptr_t;
using std::holds_alternative;


// Constructors
JSONValue::JSONValue() : value(nullptr) {}
JSONValue::JSONValue(nullptr_t) : value(nullptr) {}
JSONValue::JSONValue(bool b) : value(b) {}
JSONValue::JSONValue(double d) : value(d) {}
JSONValue::JSONValue(const string& s) : value(s) {}
JSONValue::JSONValue(const JSONObject& obj) : value(obj) {}
JSONValue::JSONValue(const JSONVector& arr) : value(arr) {}



