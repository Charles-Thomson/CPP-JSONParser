#ifndef JSONVALUE_STRUCT_H
#define JSONVALUE_STRUCT_H

#include<iostream>
#include<variant>
#include<String>
#include<unordered_map>
#include<vector>
#include<memory>
#include <variant>
#include <optional>

using std::string;
using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::variant;
using std::nullptr_t;
using std::optional;
using std::nullopt;
using std::visit;
using std::decay_t;
using std::is_same_v;


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

    template <typename T>
    optional<T> get() const {
        if (auto ptr = get_if<T>(&value)) {
            return *ptr;
        }
        return nullopt; // Empty if no type match
     
    }

    const JSONValue::JSONType& getValue() const {
        return value;
    }

    string getType() const {
        return visit([](const auto& val) -> string {
            using T = decay_t<decltype(val)>;  // Get type without const/reference
            if constexpr (is_same_v<T, nullptr_t>) return "null";
            else if constexpr (is_same_v<T, bool>) return "bool";
            else if constexpr (is_same_v<T, double>) return "double";
            else if constexpr (is_same_v<T, string>) return "string";
            else if constexpr (is_same_v<T, JSONObject>) return "JSONObject";
            else if constexpr (is_same_v<T, JSONArray>) return "JSONArray";
            else return "unknown";
            }, value);
    }



};


#endif // !JSONVALUE_STRUCT_H
