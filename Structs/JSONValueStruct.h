#ifndef JSONVALUE_STRUCT_H
#define JSONVALUE_STRUCT_H

#include<iostream>
#include<variant>
#include<String>
#include<unordered_map>
#include<vector>
#include<memory>
#include <variant>

using std::string;
using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::variant;
using std::nullptr_t;

struct JSONValue;

using JSONObject = unordered_map<string, shared_ptr<JSONValue>>;
using JSONArray = vector<shared_ptr<JSONValue>>;

struct JSONValue {
    using JSONType = variant<nullptr_t, bool, double, string, JSONObject, JSONArray>;

    JSONType value;

    JSONValue();
    JSONValue(nullptr_t);  // Declaration only
    JSONValue(bool b);
    JSONValue(double d);
    JSONValue(const string& s);
    JSONValue(const JSONObject& obj);
    JSONValue(const JSONArray& arr);



};


#endif // !JSONVALUE_STRUCT_H
